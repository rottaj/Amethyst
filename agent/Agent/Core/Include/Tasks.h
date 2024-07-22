//
// Created by j4ck on 3/22/24.
//

#ifndef AGENT_TASKS_H
#define AGENT_TASKS_H
#include <windows.h>

BOOL TaskController(IN DWORD dwTaskId, IN PCHAR pTaskArgs, OUT PBYTE *pTaskOutput);

#endif //AGENT_TASKS_H
