//
// Created by j4ck on 3/20/24.
//
#include "../../Amethyst.h"
#include "Widgets/AgentSessionTable.h"

#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H

namespace Amethyst{
    class Controller {
    private:
        // Functions
        bool Decode();
        bool Encode();
        void FindReceiverController(QString jsonKey, QJsonObject jsonData);
        void AddEventToEventViewerTab(QString event); // TODO Replace with a struct... The only event right now is a new operator connection.
        void AddAgentToSessionTable(Amethyst::Util::Agent agentStruct);
        void AddTaskOutputToCommanderTab(int agentId, QString taskOutput);
        void AddAgentToGlobalState(Amethyst::Util::Agent agentStruct);


        void AddListenerToListenerTable(Amethyst::Util::Listener listenerStruct);

        // These functions are used when dispatching commands to teamserver.

        // These functions are used when the client fetches ALL items from teamserver. Eventually migrate this to DB manager.
        // TODO Change these names to something btter
        void HandleNewAgent(QJsonValue agent);
        void HandleNewListener(QJsonValue listener);


    public:
        Controller();
        void PacketReceiver(QByteArray packet); // Handles a new Socket packet and passes to the respective private functions.

        void DispatchAgentCommand(Amethyst::Util::AgentCommand agentCommand); // Dispatches agent command to teamserver.
        void DispatchNewListener(Amethyst::Util::Listener); // Dispatches a new listener to teamserver.
        ~Controller();
    };
}

#endif //CLIENT_CONTROLLER_H
