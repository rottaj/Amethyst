//
// Created by j4ck on 3/17/24.
//
#include "../../Include/Amethyst/AppManager.h"
#include "../../Include/Amethyst/Controller.h"
#include "../../Include/Amethyst/MainWindow.h"
#include "../../Include/Amethyst/Widgets/AgentCommanderTab.h"
#include "../../Include/Amethyst/Widgets/AgentSessionTable.h"
#include "../../Include/Amethyst/Screens/AgentScreen.h"
#include "../../Include/Amethyst/Screens/ListenerScreen.h"
#include "../../Include/Amethyst/Screens/BuilderScreen.h"
#include "../../Include/Amethyst/Widgets/ListenerTable.h"
#include <QWebSocket>
#include <QObject>
#include <QUrl>
#include <QDebug>

#include "../../Amethyst.h"
// Include other widget headers...

/*
 * This is the bread and butter.
 * It creates instance of predefined Widgets (In namespace) and controls the flow of the program.
 *
 */

namespace Amethyst {
    /* Constructor: Initializes widgets & other variables.*/
    AppManager::AppManager()
    {
        QMainWindow* mainWindow = new QMainWindow();
        mainWindow->resize(1200, 600);

        /* Construct Agent Screen */
        GlobalUI::GlobalAgentScreen = new Amethyst::Screens::AgentScreen;
        GlobalUI::GlobalAgentSessionTable = new Amethyst::Widgets::AgentSessionTable;
        GlobalUI::GlobalAgentCommanderTab = new Amethyst::Widgets::AgentCommanderTab;
        /* Construct Listener Screen */
        GlobalUI::GlobalListenerScreen = new Amethyst::Screens::ListenerScreen;
        GlobalUI::GlobalListenerTable = new Amethyst::Widgets::ListenerTable;


        GlobalUI::GlobalBuilderScreen = new Amethyst::Screens::BuilderScreen;

        RealStealMainWindow = new Amethyst::MainWindow(mainWindow);

    }

    /* Start of the program. Parses command line, starts DB Manager, Initialized sockets, set's login Dialog, etc. */
    void AppManager::Init(int argc, char** argv)
    {
        // Parse command line
        // Start DB Manager
        // This will be called in Dialogs/Login.
        // TODO add info parameter (username + password)

        /* Initialize Global Controller */
        GlobalState::GlobalController       = new Amethyst::Controller();
        /* Initialize Global Socket *Initialized in Constructor* */
        SocketHandler    = new Amethyst::SocketHandler();
    }
    /* Starts User Interface */
    void AppManager::StartUserInterface() {
        //RealStealMainWindow->resize(1200, 600);
        RealStealMainWindow->show();
    }

    /* Destructor */
    AppManager::~AppManager() {

    }

} // namespace MyApp