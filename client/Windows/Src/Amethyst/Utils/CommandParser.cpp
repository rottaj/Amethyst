//
// Created by j4ck on 3/21/24.
//
#include <QDebug>
#include "../../../Amethyst.h"
#include "../../../Include/Amethyst/Utils/CommandParser.h"
#include "../../../Include/Amethyst/Widgets/AgentCommanderTab.h"
#include "../../../Include/Amethyst/Controller.h"

using namespace Amethyst;
namespace Amethyst {
    // The commandId will have the name consensus as the teamserver.
    // TODO move the if's down to CommandParser
    Amethyst::Util::AgentCommand Util::CreateAgentCommand(int agentId, QString plainTextCommand) {
        Amethyst::Util::AgentCommand command;
        command.AgentUniqueId = agentId;
        QStringList commandList = plainTextCommand.split(" ");
        qDebug() << "[+] CommandParser: (commandList)" << commandList;
        if (commandList[0] == "ls") {
            command.CommandId = 0x01;
            if (commandList.length() > 1) {
                command.Arguments = QString(commandList[1]);
            }
        }
        if (commandList[0] == "cd") {
            command.CommandId = 0x02;
            if (commandList.length() > 1) {
                command.Arguments = QString(commandList[1]);
            }
        }
        if (commandList[0] == "processes") {
            command.CommandId = 0x03;
        }
        if (commandList[0] == "pwd") {
            command.CommandId = 0x04;
        }
        if (commandList[0] == "cat") {
            command.CommandId = 0x05;
            if (commandList.length() > 1) {
                command.Arguments = QString(commandList[1]);
            }
        }
        if (commandList[0] == "sleep") {
            command.CommandId = 0x06;
            if (commandList.length() > 1) {
                command.Arguments = QString(commandList[1]);
            }
        }
        return command;
    }


    /* This is the main Command Parser. This determines what command will be dispatched to teamserver */
    void Util::CommandParser(int agentId, QString plainTextCommand) {
        if (plainTextCommand == QString("help")) {

            QString taskOutput = QString("<table> <style>{"
                                                       "    border-collapse: collapse;"
                                                       "    width: 100%;"
                                                       "}"
                                                       "th, td {"
                                                       "    border: 1px solid black;"
                                                       "    padding: 8px;"
                                                       "    text-align: left;"
                                                       "}</style>"
                                         "<tr> <th>Command</th><th>Description</th><th> Noise Level </th>"
                                         "<tr> <td>whoami</td><td >Display current user.</td><td>Low</td></tr>"
                                         "<tr> <td>sleep</td><td>Change agent sleep time.</td><td>Medium</td></tr>"
                                         "<tr> <td>ls</td><td>List directory.</td><td>Low</td></tr>"
                                         "<tr> <td>pwd</td><td>Print working directory.</td><td>Low</td></tr>"
                                         "<tr> <td>cat</td><td>Prints contents of file.</td><td>Medium</td></tr>"
                                         "<tr> <td>processes</td><td>List running processes.</td><td>Low</td></tr>"
                                         "<tr> <td>services</td><td>List running services.</td><td>Low</td></tr>"
                                         "<tr> <td>ipconfig</td><td>List network adapter information.</td><td>Medium</td></tr>"
                                         "<tr> <td>cmd</td><td>Execute command through cmd.exe.</td><td>High</td></tr>"
                                         "<tr> <td>screenshot</td><td>Take a screenshot of the users desktop.</td><td>High</td></tr>"
                                         "<tr> <td>webcam</td><td>Snap a picture through the users webcam.</td><td>High</td></tr>"
                                         "</table>");
            GlobalUI::GlobalAgentCommanderTab->UpdateCommandHistory(agentId, taskOutput);
        }
        else if (plainTextCommand == QString("whoami")) {
            // Replace with an actual agent task? ( All this does is print the saved agent from GlobalState )
            QString taskOutput = GlobalState::Agents[GlobalState::Agents.size()-1].ComputerName + "\\" + GlobalState::Agents[GlobalState::Agents.size()-1].Username;
            GlobalUI::GlobalAgentCommanderTab->UpdateCommandHistory(agentId, taskOutput);
        }
        else {
            Amethyst::Util::AgentCommand agentCommandStruct = Amethyst::Util::CreateAgentCommand(agentId, plainTextCommand);
            GlobalState::GlobalController->DispatchAgentCommand(agentCommandStruct);

            // Write Task bytes sent to CommanderTab
            QStringList commandList = plainTextCommand.split(" ");
            if (commandList.length() > 1) {
                QString taskOutput = QString("<font color=\"#66FF00\">[+]</font> Sent Task to Agent [<font color=\"red\">" + QString::number(commandList[1].size()+8) +"  bytes</font>]<br>");
                GlobalUI::GlobalAgentCommanderTab->UpdateCommandHistory(agentId, taskOutput);
            } else {
                QString taskOutput = QString("<font color=\"#66FF00\">[+]</font> Sent Task to Agent [<font color=\"red\">8 bytes</font>]<br>");
                GlobalUI::GlobalAgentCommanderTab->UpdateCommandHistory(agentId, taskOutput);
            }
        }
    }
}
