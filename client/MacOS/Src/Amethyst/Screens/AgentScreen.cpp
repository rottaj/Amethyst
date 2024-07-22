//
// Created by j4ck on 4/7/24.
//

#include "../../../Include/Amethyst/Screens/AgentScreen.h"
#include "../../../Include/Amethyst/Widgets/AgentCommanderTab.h"
#include "../../../Include/Amethyst/Widgets/AgentSessionTable.h"
#include <QSplitter>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSizePolicy>


using namespace Amethyst::Widgets;

namespace Amethyst {
    void Screens::AgentScreen::Setup(/*QWidget* Main*/) {

        /* Create & Set CentralWidget*/
        AgentScreenMainWidget = new QWidget(/*Main*/); // TODO IF NOT WORKING ADD GLOBALUI::MAINSTACKEDWIDGET

//#if 0
        AgentScreenMainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        /* Create MainGridLayout */
        AgentScreenLayout = new QVBoxLayout(/*AmethystAgentMenuWidget*/);
        AgentScreenLayout->setContentsMargins( 0, 0, 0, 0 );

        /*
        if (!Amethyst::Widgets::GlobalAgentSessionTable) {
            Amethyst::Widgets::GlobalAgentSessionTable = new Amethyst::Widgets::AgentSessionTable;
        }
        */
        /* Create Agent Session Table Widget */
        QWidget* AgentTableContainer = new QWidget();
        //AgentTableContainer->setStyleSheet("background-color: red;");
        GlobalUI::GlobalAgentSessionTable->Setup(AgentTableContainer);


        /* Create Agent Commander Tab Widget */

        QWidget* AgentTabContainer = new QWidget();
        //AgentTabContainer->setStyleSheet("background-color: red;");
        GlobalUI::GlobalAgentCommanderTab->Setup(AgentTabContainer);


        //GlobalUI::GlobalAgentCommanderTab->Setup(AgentTabContainer);


        /* Container Layout */
        QSplitter* splitter = new QSplitter();

        /* Add Agent Table to Main Widget */


        splitter->addWidget(AgentTableContainer);
        splitter->addWidget(AgentTabContainer);
        AgentScreenLayout->addWidget(splitter);
        splitter->setOrientation(Qt::Vertical);
        AgentScreenMainWidget->setLayout(AgentScreenLayout);
//#endif
    }
}
