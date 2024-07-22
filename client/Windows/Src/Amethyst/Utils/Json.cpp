#include <QJsonObject>
#include "../../../Amethyst.h"
#include "../../../Include/Amethyst/Utils/Json.h"

namespace Amethyst{

    Amethyst::Util::Agent Util::JsonToAgentStruct(const QJsonObject &obj) {

        Amethyst::Util::Agent agent;
        // TODO add a check to see if obj == QJsonObject
        if (!obj.isEmpty()) {
            agent.Id 				= obj["Id"].toInt();
            agent.UniqueId 			= obj["UniqueId"].toString();
            agent.Listener 			= obj["Listener"].toString();
            agent.Username 			= obj["UserName"].toString();
            agent.ComputerName 		= obj["ComputerName"].toString();
            agent.WindowsVersion 	= obj["WindowsVersion"].toString();
            agent.ExternalIp 		= obj["ExternalIp"].toString();
            agent.InternalIp 		= obj["InternalIp"].toString();
            agent.LastCallHome 		= obj["LastCallHome"].toInt();
            agent.Pid				= obj["PID"].toInt();
            agent.ProcessName       = obj["ProcessName"].toString();
            agent.Sleep				= obj["Sleep"].toInt();
        }
        return agent;
    }
    Amethyst::Util::Listener Util::JsonToListenerStruct(const QJsonObject &obj) {
        Amethyst::Util::Listener listener;
        // TODO add a check to see if obj == QJsonObject
        if (!obj.isEmpty()) {
            listener.Id 				= obj["Id"].toInt();
            listener.Name 			    = obj["Name"].toString();
            listener.Host 			    = obj["Host"].toString();
            listener.Uri 			    = obj["Uri"].toString();
            listener.Port				= obj["Port"].toInt();

        }
        return listener;
    }

    QJsonObject Util::CreateAgentTaskPackage(Amethyst::Util::AgentCommand command) {
        QJsonObject innerObj;
        innerObj["AgentId"] = command.AgentUniqueId;
        innerObj["CommandId"] = command.CommandId;
        innerObj["Arguments"] = command.Arguments;

        QJsonObject mainObj;
        mainObj["Head"] = "AGENT_TASK";
        mainObj["Data"] = innerObj;

        return mainObj;

    }

    QJsonObject Util::CreateNewListenerPackage(Amethyst::Util::Listener listener) {
        QJsonObject innerObj;
        innerObj["Name"] = listener.Name;
        innerObj["Host"] = listener.Host;
        innerObj["Port"] = listener.Port;
        innerObj["Uri"] = listener.Uri;

        QJsonObject mainObj;
        mainObj["Head"] = "NEW_LISTENER_CREATED";
        mainObj["Data"] = innerObj;

        return mainObj;
    }
}
