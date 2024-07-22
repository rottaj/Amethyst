//
// Created by j4ck on 3/21/24.
//

#ifndef CLIENT_COMMANDPARSER_H
#define CLIENT_COMMANDPARSER_H
#include "../../../Amethyst.h"

namespace Amethyst {
    Amethyst::Util::AgentCommand Util::CreateAgentCommand(int agentId, QString plainTextCommand);
    void Util::CommandParser(int agentId, QString plainTextCommand);
}

#endif //CLIENT_COMMANDPARSER_H
