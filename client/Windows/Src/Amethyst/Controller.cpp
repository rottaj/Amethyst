//
// Created by j4ck on 3/20/24.
//
#include "../../Include/Amethyst/Controller.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "../../Include/Amethyst/Widgets/AgentSessionTable.h"
#include "../../Include/Amethyst/Widgets/ListenerTable.h"
#include "../../Include/Amethyst/Widgets/AgentCommanderTab.h"
#include "../../Include/Amethyst/Utils/Json.h"
#include "../../Amethyst.h"

using namespace Amethyst;
Controller::Controller() {
}


/* This is called when a new binary message is received in the socket connection */
void Controller::PacketReceiver(QByteArray packet) {
    QJsonDocument jsonDocument = QJsonDocument::fromJson(packet);
    QJsonObject jsonObject = jsonDocument.object();

    /* Loop through keys. Only supposed to be 1 key at a time (Head) but handle any descrepencies.*/
    QJsonObject dataObject = jsonObject.value("Data").toObject();
    FindReceiverController(jsonObject.value("Head").toString(), dataObject);
}

/* This function calls the appropriate controller depending on the message body received */
void Controller::FindReceiverController(QString jsonKey, QJsonObject jsonData) {
    qDebug() << "JSONKEY" << jsonKey;
    if (jsonKey == "NEW_AGENT") {
        Controller::HandleNewAgent(jsonData);
    }
    else if (jsonKey == "AGENT_TASK_RESPONSE") {
        qDebug() << "TASK RESPONSE: " << jsonData;
        Controller::AddTaskOutputToCommanderTab(jsonData.value("AgentId").toInt(), jsonData.value("TaskOutput").toString());
    }
    else if (jsonKey == "OPERATOR_CONNECTED") {
        qDebug() << "OPERATOR CONNECTED: " << jsonData;
        Controller::AddEventToEventViewerTab("<font color=\"#66FF00\">[+]</font> " + jsonData.value("Name").toString() + " Connected<br>");
    }
    else if (jsonKey == "NEW_LISTENER") {
        qDebug() << "NEW LISTENER CREATED " << jsonData;
        Controller::HandleNewListener(jsonData);

    }
}

// TODO I SHOULD DO SOMETHING ABOUT THESE. Basically, this is just an extra layer of abstraction.

void Controller::AddEventToEventViewerTab(QString event) {
    GlobalUI::GlobalAgentCommanderTab->UpdateEventViewerHistory(event);
}

void Controller::AddTaskOutputToCommanderTab(int agentId, QString taskOutput) {
    GlobalUI::GlobalAgentCommanderTab->UpdateCommandHistory(agentId, taskOutput);
    GlobalState::Agents[agentId].LastCallHome = 0;
}

/* Add Agent to Session Table */
void Controller::AddAgentToSessionTable(Amethyst::Util::Agent agentStruct) {

        GlobalUI::GlobalAgentSessionTable->AddAgentSessionToTable(agentStruct);

}

void Controller::AddListenerToListenerTable(Amethyst::Util::Listener listenerStruct) {

    GlobalUI::GlobalListenerTable->AddListenerToListenerTable(listenerStruct);

}

/* Add Agent to Global State */
void Controller::AddAgentToGlobalState(Amethyst::Util::Agent agentStruct) {
    GlobalState::Agents.insert(GlobalState::Agents.end(), agentStruct);
}


void Controller::HandleNewAgent(QJsonValue agent) {
    QJsonObject agentObj = agent.toObject();

    Amethyst::Util::Agent agentStruct = Util::JsonToAgentStruct(agentObj);

    QString output = QString ("<br> <font color=\"#66FF00\">[+]</font> Infected New Agent: " + agentStruct.ComputerName + "\\" + agentStruct.Username + " ! Connected from: " + agentStruct.ExternalIp + "<br>");
    GlobalUI::GlobalAgentCommanderTab->UpdateEventViewerHistory(output);
    Controller::AddAgentToGlobalState(agentStruct);
    Controller::AddAgentToSessionTable(agentStruct);
}


void Controller::HandleNewListener(QJsonValue listener) {
    QJsonObject agentObj = listener.toObject();

    Amethyst::Util::Listener listenerStruct = Util::JsonToListenerStruct(agentObj);

    QString output = QString ("<br> <font color=\"#66FF00\">[+]</font> New Listener Created: " + listenerStruct.Name + "\thttp://" + listenerStruct.Host + ":" + QString::number(listenerStruct.Port) + listenerStruct.Uri  + "<br>");
    GlobalUI::GlobalAgentCommanderTab->UpdateEventViewerHistory(output);
    //Controller::AddAgentToGlobalState(agentStruct); // TODO Add listener to Global State
    Controller::AddListenerToListenerTable(listenerStruct);
}




/* Start of Dispatch functions. These functions dispatch commands to teamserver. */
// Called in CommandParser.cpp // TODO <--- change this.. make it better.
void Controller::DispatchAgentCommand(Amethyst::Util::AgentCommand agentCommand) {
    QJsonObject package = Amethyst::Util::CreateAgentTaskPackage(agentCommand);
    qDebug() << "[+] Controller (DispatchAgentCommand)" << package;
    QJsonDocument jsonDoc(package);
    QByteArray bytes = jsonDoc.toJson();
    GlobalState::SocketConnection->sendBinaryMessage(bytes);
    // TODO once complete, add [+] Dispatched command to agent to the textexit ConsoleHistory.
}

void Controller::DispatchNewListener(Amethyst::Util::Listener newListener) {
    QJsonObject package = Amethyst::Util::CreateNewListenerPackage(newListener);
    qDebug() << "[+] Controller (DispatchNewListener)" << package;
    QJsonDocument jsonDoc(package);
    QByteArray bytes = jsonDoc.toJson();
    GlobalState::SocketConnection->sendBinaryMessage(bytes);
}

/* Destructor */
Controller::~Controller() {

}