//
// Created by j4ck on 3/19/24.
//

#ifndef CLIENT_JSON_H
#define CLIENT_JSON_H
#include "../../../Amethyst.h"
#include <QJsonObject>

namespace Amethyst{

    Amethyst::Util::Agent Util::JsonToAgentStruct(const QJsonObject &obj);
    QJsonObject Util::CreateAgentTaskPackage(Amethyst::Util::AgentCommand command);
}

#endif //CLIENT_JSON_H
