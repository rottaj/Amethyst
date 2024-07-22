//
// Created by j4ck on 3/17/24.

//
#include "../../Include/Amethyst/MainWindow.h"
#include "../../Amethyst.h"
#include "../../Include/Amethyst/Widgets/AgentCommanderTab.h"
#include "../../Include/Amethyst/Screens/AgentScreen.h"
#include "../../Include/Amethyst/Screens/ListenerScreen.h"
#include "../../Include/Amethyst/Screens/BuilderScreen.h"
#include <QWidget>
#include <QIcon>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSizePolicy>
#include <QIcon>
#include <QSplitter>

using namespace Amethyst::Widgets;

namespace Amethyst{

    MainWindow::MainWindow(QWidget *parent) // Initializer
            : QMainWindow(parent)
    {
        // Implement MainWindow constructor
        Setup(parent);

    }
    void MainWindow::Setup(QWidget *parent) {
        this->setWindowTitle("Amethyst Operator");
        QIcon iconMain("C:\\Users\\j4ck\\Documents\\Projects\\Amethyst\\client\\Assets\\diamond_2.png");
        this->setWindowIcon(iconMain);
        // TODO NOTE ( CREATE MAIN LAYOUT & MAIN STACKED WIDGET )
        CentralWidget = new QWidget(parent);
        CentralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        setCentralWidget(CentralWidget);
        MainStackedWidget = new QStackedWidget;
        MainGridLayout = new QHBoxLayout(/*AmethystAgentMenuWidget*/);
        MainGridLayout->setContentsMargins( 0, 0, 0, 0 );


        // TODO NOTE (BELOW CREATERS THE HORIZONTAL MENU BAR TO SWITCH STACKED WIDGETS )
        AmethystSideBarMenuWidget = new QWidget();
        AmethystSideBarMenuLayout = new QVBoxLayout(/*AmethystAgentMenuWidget*/);
        AmethystSideBarMenuLayout->setAlignment(Qt::AlignTop);
        //AmethystSideBarMenuLayout->setAlignment(Qt::AlignHCenter);


        AmethystSideBarMenuLayout->setContentsMargins( 0, 0, 0, 0 );
        QWidget*          AmethystButtonBox             = new QWidget();
        QVBoxLayout*      AmethystButtonLayout          = new QVBoxLayout();
        QLabel*           AmethystLabel                 = new QLabel("Amethyst");
        QPushButton*      SwitchToAgentScreen           = new QPushButton();

        AmethystButtonLayout->addWidget(SwitchToAgentScreen);
        AmethystButtonLayout->addWidget(AmethystLabel);
        QIcon iconAmethyst("C:\\Users\\j4ck\\Documents\\Projects\\Amethyst\\client\\Assets\\diamond_2.png");
        SwitchToAgentScreen->setIcon(iconAmethyst);
        SwitchToAgentScreen->setIconSize(QSize(50, 50)); // Adjust size as needed
        AmethystButtonBox->setLayout(AmethystButtonLayout);
        AmethystButtonLayout->setAlignment(Qt::AlignCenter);
        AmethystButtonBox->setStyleSheet("border: none; padding-left: 10px;");


        QWidget*         ListenerButtonBox              = new QWidget();
        QVBoxLayout*     ListenerButtonLayout           = new QVBoxLayout();
        QLabel*          ListenerLabel                  = new QLabel("Listeners");
        QPushButton*     SwitchToListenersScreen        = new QPushButton();

        ListenerButtonLayout->addWidget(SwitchToListenersScreen);
        ListenerButtonLayout->addWidget(ListenerLabel);
        QIcon iconListener("C:\\Users\\j4ck\\Documents\\Projects\\Amethyst\\client\\Assets\\listening.png");
        SwitchToListenersScreen->setIcon(iconListener);
        SwitchToListenersScreen->setIconSize(QSize(40, 40)); // Adjust size as needed
        ListenerButtonBox->setLayout(ListenerButtonLayout);
        ListenerButtonLayout->setAlignment(Qt::AlignCenter);
        ListenerButtonBox->setStyleSheet("border: none; padding-left: 10px;");



        QWidget*        AgentBuilderButtonBox           = new QWidget();
        QVBoxLayout*    AgentBuilderButtonLayout        = new QVBoxLayout();
        QLabel*         AgentBuilderLabel               = new QLabel("Agent Builder");
        QPushButton*    SwitchToAgentBuilderScreen      = new QPushButton();

        AgentBuilderButtonLayout->addWidget(SwitchToAgentBuilderScreen);
        AgentBuilderButtonLayout->addWidget(AgentBuilderLabel);
        QIcon iconAgentBuilder("C:\\Users\\j4ck\\Documents\\Projects\\Amethyst\\client\\Assets\\bug.png");
        SwitchToAgentBuilderScreen->setIcon(iconAgentBuilder);
        SwitchToAgentBuilderScreen->setIconSize(QSize(40, 40)); // Adjust size as needed
        AgentBuilderButtonBox->setLayout(AgentBuilderButtonLayout);
        AgentBuilderButtonLayout->setAlignment(Qt::AlignCenter);
        AgentBuilderButtonBox->setStyleSheet("border: none; padding-left: 10px;");



        QWidget*        LootButtonBox                   = new QWidget();
        QVBoxLayout*    LootButtonLayout                = new QVBoxLayout();
        QLabel*         LootLabel                       = new QLabel("My Loot");
        QPushButton*    SwitchToLootScreen              = new QPushButton();
        LootButtonLayout->addWidget(SwitchToLootScreen);
        LootButtonLayout->addWidget(LootLabel);
        QIcon iconLoot("C:\\Users\\j4ck\\Documents\\Projects\\Amethyst\\client\\Assets\\money-bag.png");
        SwitchToLootScreen->setIcon(iconLoot);
        SwitchToLootScreen->setIconSize(QSize(40, 40)); // Adjust size as needed
        LootButtonBox->setLayout(LootButtonLayout);
        LootButtonLayout->setAlignment(Qt::AlignCenter);
        LootButtonBox->setStyleSheet("border: none; padding-left: 10px;");


        QWidget*        WorkflowButtonBox                   = new QWidget();
        QVBoxLayout*    WorkflowButtonLayout                = new QVBoxLayout();
        QLabel*         WorkflowLabel                       = new QLabel("Workflows");
        QPushButton*    SwitchToWorkFlowScreen              = new QPushButton();
        WorkflowButtonLayout->addWidget(SwitchToWorkFlowScreen);
        WorkflowButtonLayout->addWidget(WorkflowLabel);
        QIcon iconWorkflow("C:\\Users\\j4ck\\Documents\\Projects\\Amethyst\\client\\Assets\\workflow.png");
        SwitchToWorkFlowScreen->setIcon(iconWorkflow);
        SwitchToWorkFlowScreen->setIconSize(QSize(40, 40)); // Adjust size as needed
        WorkflowButtonBox->setLayout(WorkflowButtonLayout);
        WorkflowButtonLayout->setAlignment(Qt::AlignCenter);
        WorkflowButtonBox->setStyleSheet("border: none; padding-left: 10px;");



        QWidget*        ChatButtonBox                   = new QWidget();
        QVBoxLayout*    ChatButtonLayout                = new QVBoxLayout();
        QLabel*         ChatLabel                       = new QLabel("Operator Chat");
        QPushButton* SwitchToChatScreen                 = new QPushButton();
        ChatButtonLayout->addWidget(SwitchToChatScreen);
        ChatButtonLayout->addWidget(ChatLabel);
        QIcon iconChat("C:\\Users\\j4ck\\Documents\\Projects\\Amethyst\\client\\Assets\\chat-box.png");
        SwitchToChatScreen->setIcon(iconChat);
        SwitchToChatScreen->setIconSize(QSize(40, 40)); // Adjust size as needed
        ChatButtonBox->setLayout(ChatButtonLayout);
        ChatButtonLayout->setAlignment(Qt::AlignCenter);
        ChatButtonBox->setStyleSheet("border: none; padding-left: 10px;");



        QWidget*        HelpButtonBox                   = new QWidget();
        QVBoxLayout*    HelpButtonLayout                = new QVBoxLayout();
        QLabel*         HelpLabel                       = new QLabel("Help & Donate");
        QPushButton*    SwitchToHelpScreen              = new QPushButton();
        HelpButtonLayout->addWidget(SwitchToHelpScreen);
        HelpButtonLayout->addWidget(HelpLabel);
        QIcon iconHelp("C:\\Users\\j4ck\\Documents\\Projects\\Amethyst\\client\\Assets\\care.png");
        SwitchToHelpScreen->setIcon(iconHelp);
        SwitchToHelpScreen->setIconSize(QSize(40, 40)); // Adjust size as needed
        HelpButtonBox->setLayout(HelpButtonLayout);
        HelpButtonLayout->setAlignment(Qt::AlignCenter);
        HelpButtonBox->setStyleSheet("border: none; padding-left: 10px;");


        AmethystSideBarMenuLayout->addSpacing(20); // Add spacing between label1 and label2
        AmethystSideBarMenuLayout->addWidget(AmethystButtonBox);
        AmethystSideBarMenuLayout->addWidget(ListenerButtonBox);
        AmethystSideBarMenuLayout->addWidget(AgentBuilderButtonBox);
        AmethystSideBarMenuLayout->addWidget(LootButtonBox);
        AmethystSideBarMenuLayout->addWidget(WorkflowButtonBox);
        AmethystSideBarMenuLayout->addWidget(ChatButtonBox);
        AmethystSideBarMenuLayout->addWidget(HelpButtonBox); // TODO ADD HELP
        AmethystSideBarMenuLayout->addSpacing(1); // Add spacing between label1 and label2
        AmethystSideBarMenuWidget->setLayout(AmethystSideBarMenuLayout);


        connect(SwitchToAgentScreen, &QPushButton::clicked, MainStackedWidget, [=] {
            MainStackedWidget->setCurrentIndex(0);
        });
        connect(SwitchToListenersScreen, &QPushButton::clicked, MainStackedWidget, [=] {
            MainStackedWidget->setCurrentIndex(1);
        });
        connect(SwitchToAgentBuilderScreen, &QPushButton::clicked, MainStackedWidget, [=] {
            MainStackedWidget->setCurrentIndex(2);
        });
        connect(SwitchToLootScreen, &QPushButton::clicked, MainStackedWidget, [=] {
            MainStackedWidget->setCurrentIndex(3);
        });
        connect(SwitchToWorkFlowScreen, &QPushButton::clicked, MainStackedWidget, [=] {
            MainStackedWidget->setCurrentIndex(4);
        });

        connect(SwitchToHelpScreen, &QPushButton::clicked, MainStackedWidget, [=] {
            MainStackedWidget->setCurrentIndex(5);
        });

        /* Create Screens (Stacked Widgets */
        GlobalUI::GlobalAgentScreen->Setup();
        GlobalUI::GlobalListenerScreen->Setup();
        GlobalUI::GlobalBuilderScreen->Setup();



        // TODO NOTE( BELOW SETS THE MAIN LAYOUT )
        /* Add StackedWidgets to MainLayout */
        // TODO Change MainGridLayout to other name
        //MainStackedWidget->addWidget(AmethystAgentMenuWidget);
        MainStackedWidget->addWidget(GlobalUI::GlobalAgentScreen->AgentScreenMainWidget);
        MainStackedWidget->addWidget(GlobalUI::GlobalListenerScreen->ListenerScreenMainWidget);
        MainStackedWidget->addWidget(GlobalUI::GlobalBuilderScreen->BuilderScreenMainWidget);
        MainGridLayout->addWidget(AmethystSideBarMenuWidget);
        MainGridLayout->addWidget(MainStackedWidget);
        CentralWidget->setLayout(MainGridLayout);


        /* Set CentralWidget size */
        CentralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        CentralWidget->setMinimumSize(1600, 900);

    }


    MainWindow::~MainWindow() { // Destructor

    }

}