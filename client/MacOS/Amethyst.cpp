//
// Created by j4ck on 3/20/24.
//

#include "Amethyst.h"
#include <QWebSocket>

using namespace Amethyst;
using namespace GlobalUI;

// Initialize Global Variables

/* Global UI */
Amethyst::Screens::AgentScreen*         GlobalUI::GlobalAgentScreen;
Amethyst::Widgets::AgentSessionTable*   GlobalUI::GlobalAgentSessionTable;
Amethyst::Widgets::AgentCommanderTab*   GlobalUI::GlobalAgentCommanderTab;


Amethyst::Screens::ListenerScreen*         GlobalUI::GlobalListenerScreen;
Amethyst::Widgets::ListenerTable*         GlobalUI::GlobalListenerTable;


Amethyst::Screens::BuilderScreen*         GlobalUI::GlobalBuilderScreen;

/* Global State */
std::vector<Amethyst::Util::Agent> GlobalState::Agents;
QWebSocket*                         GlobalState::SocketConnection;
Amethyst::Controller*              GlobalState::GlobalController;