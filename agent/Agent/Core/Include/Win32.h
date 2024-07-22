//
// Created by j4ck on 3/15/24.
//
#include <windows.h>
#include <winternl.h>
#include <ntdef.h>
#include <iptypes.h>

#ifndef AGENT_WIN32_H
#define AGENT_WIN32_H

#endif //AGENT_WIN32_H

HMODULE GetModuleHandleC(IN LPCWSTR szModuleName);

PVOID GetProcAddressC(IN HMODULE hModule, IN LPCSTR lpProcName);

typedef DWORD (WINAPI* fnGetVersion)();

typedef BOOL (WINAPI* fnGetComputerNameW)(OUT LPWSTR lpBuffer, IN OUT LPDWORD nSize);

typedef BOOL (WINAPI* fnGetUserNameW)(OUT LPWSTR lpBuffer, IN OUT LPDWORD nSize);

typedef DWORD (WINAPI* fnGetProcessId)(IN HANDLE Process);

typedef HANDLE (WINAPI* fnGetCurrentProcess)();

typedef HANDLE (WINAPI* fnOpenProcess)(IN DWORD dwDesiredAccess, IN BOOL bInheritHandle, IN DWORD dwProcessId);

typedef DWORD (WINAPI* fnGetProcessImageFileNameW)(IN HANDLE hProcess, OUT LPWSTR lpImageFileName, DWORD nSize);


typedef ULONG (WINAPI* fnGetAdaptersAddresses)(IN ULONG Family, IN ULONG Flags, OUT PIP_ADAPTER_INFO AdapterInfo, IN OUT PULONG SizePointer);

typedef ULONG (WINAPI* fnGetAdaptersInfo)(OUT PIP_ADAPTER_INFO AdapterInfo, IN OUT PULONG SizePointer);

typedef void (WINAPI* fnSleep)(IN DWORD dwMilliSeconds);



// TODO Move NTAPI to it's own file
typedef NTSTATUS (NTAPI* fnNtQuerySystemInformation)(
        IN SYSTEM_INFORMATION_CLASS     SystemInformationClass,
        IN OUT PVOID                    SystemInformation,
        IN ULONG                        SystemInformationLength,
        OUT OPTIONAL PULONG             ReturnLength
);