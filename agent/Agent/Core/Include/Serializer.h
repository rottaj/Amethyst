//
// Created by j4ck on 3/15/24.
//
#include <windows.h>
#include "Agent.h"
#ifndef AGENT_SERIALIZER_H
#define AGENT_SERIALIZER_H

#endif //AGENT_SERIALIZER_H

BOOL JsonCreateInitFromAgentInfo(IN AgentInfo agentInfo, IN OUT PBYTE *buffer);

BOOL JsonCreateCheckIn(OUT PBYTE *pOutputBuffer, IN DWORD dwTaskId, IN PCHAR pTaskArgs, IN PBYTE pTaskOutput);

BOOL JsonParseResponseFromC2(IN PCHAR responseStringJson, OUT PDWORD dwTaskId, OUT PCHAR *pTaskArgs);
