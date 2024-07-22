//
// Created by j4ck on 3/17/24.
//

#ifndef CLIENT_AMETHYST_H
#define CLIENT_AMETHYST_H

#include <QString>
#include <QJsonObject>
#include <QTcpSocket>
#include <QWebSocket>

namespace Amethyst{
    class MainWindow; // The Main Window UI container
    class SocketHandler; // Handles the current socket connection.
    class Controller; // Takes data from socket and updates UI. Also dispatches commands to teamserver.

    namespace Screens {
        class AgentScreen;
        class ListenerScreen;
        class BuilderScreen;
    }
    namespace Widgets {
        class AgentCommanderTab;
        class AgentSessionTable;

        class ListenerTable;
        // Global Variables.

    }
    namespace Dialogs {
        class ListenerDialog;
    }

    class AppManager; // {

    namespace Util {
        typedef struct {
            int 	    Id;
            QString     UniqueId;
            QString     Listener;
            QString     ComputerName;
            QString     Username;
            QString     ExternalIp;
            QString     InternalIp;
            int 	    Pid;
            QString     ProcessName;
            QString     WindowsVersion;
            int 	    Sleep;
            int         LastCallHome;
        } Agent;

        typedef struct {
            int     AgentUniqueId;
            int     CommandId;
            QString Arguments;
        } AgentCommand;

        typedef struct {
            int Id;
            QString Name;
            QString Host;
            int Port;
            QString Uri; //TODO  This will eventually be a <vector> of Uri's
        } Listener;

        typedef struct {
            QString head; // This like the HTTP route. /AGENTS, AGENT_TASK, LISTENERS, etc.
            QJsonObject* json;
        } SocketPackage; // TODO Implement this? Why is it not showing up... am i not using this?

        // These are Utility commands.
        // TODO combine the below json functions into one if can.
        Amethyst::Util::Agent              JsonToAgentStruct(const QJsonObject& obj);
        Amethyst::Util::Listener              JsonToListenerStruct(const QJsonObject& obj);
        Amethyst::Util::AgentCommand       CreateAgentCommand(int agentId, const QString plainTextCommand);
        void                               CommandParser(int agentId, const QString plainTextCommand);
        QJsonObject                        CreateAgentTaskPackage(Amethyst::Util::AgentCommand command);
        QJsonObject                        CreateNewListenerPackage(Amethyst::Util::Listener listener);
    }


}


// Global Variables
namespace GlobalUI {
    extern Amethyst::Screens::AgentScreen*              GlobalAgentScreen;
    extern Amethyst::Widgets::AgentSessionTable*        GlobalAgentSessionTable;
    extern Amethyst::Widgets::AgentCommanderTab*        GlobalAgentCommanderTab;

    extern Amethyst::Screens::ListenerScreen*           GlobalListenerScreen;
    extern Amethyst::Screens::BuilderScreen*            GlobalBuilderScreen;
    extern Amethyst::Widgets::ListenerTable*            GlobalListenerTable;
}

namespace GlobalState {
    extern Amethyst::Controller*                    GlobalController;
    extern QWebSocket*                              SocketConnection;
    extern std::vector<Amethyst::Util::Agent>       Agents;
}

#endif //CLIENT_REALSTEAL_H
