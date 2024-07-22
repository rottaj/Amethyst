//
// Created by j4ck on 3/18/24.
//


#include "../../../Include/Amethyst/Widgets/AgentSessionTable.h"
#include "../../../Include/Amethyst/Widgets/AgentCommanderTab.h"
#include "../../../Amethyst.h"
#include <QTimer>
#include <QHeaderView>
#include <QObject>
#include <QAbstractItemView>
#include <QSize>
#include <QMenu>
#include <QSizePolicy>
#include <QGridLayout>
#include <QAction>

namespace Amethyst::Widgets {
    void AgentSessionTable::Setup(QWidget* parent) {

        QGridLayout* GridLayout = new QGridLayout(parent); // This is required for stretch
        AgentSessionTableWidget = new QTableWidget(parent);
        GridLayout->addWidget(AgentSessionTableWidget);
        //AgentSessionTableWidget->setStyleSheet("background-color: blue;");
        AgentSessionTableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        AgentSessionTableWidget->setColumnCount(11);
        AgentSessionTableWidget->setRowCount(2);

        TitleAgentIcon   = new QTableWidgetItem( " "      ); // ICON
        TitleAgentID   = new QTableWidgetItem( "ID"       );
        TitleExternal  = new QTableWidgetItem( "External" );
        TitleInternal  = new QTableWidgetItem( "Internal" );
        TitleUser      = new QTableWidgetItem( "User"     );
        TitleComputer  = new QTableWidgetItem( "Computer" );
        TitleWinVersion = new QTableWidgetItem( "Windows Version"       );
        TitleProcess   = new QTableWidgetItem( "Process"  );
        TitleProcessId = new QTableWidgetItem( "PID"      );
        TitleLast      = new QTableWidgetItem( "Last"     );
        TitleHealth    = new QTableWidgetItem( "Health"   );

        AgentSessionTableWidget->setHorizontalHeaderItem( 0, TitleAgentIcon     );
        AgentSessionTableWidget->setHorizontalHeaderItem( 1, TitleAgentID       );
        AgentSessionTableWidget->setHorizontalHeaderItem( 2, TitleExternal      );
        AgentSessionTableWidget->setHorizontalHeaderItem( 3, TitleInternal      );
        AgentSessionTableWidget->setHorizontalHeaderItem( 4, TitleUser          );
        AgentSessionTableWidget->setHorizontalHeaderItem( 5, TitleComputer      );
        AgentSessionTableWidget->setHorizontalHeaderItem( 6, TitleWinVersion    );
        AgentSessionTableWidget->setHorizontalHeaderItem( 7, TitleProcess       );
        AgentSessionTableWidget->setHorizontalHeaderItem( 8, TitleProcessId     );
        AgentSessionTableWidget->setHorizontalHeaderItem( 9, TitleLast          );
        AgentSessionTableWidget->setHorizontalHeaderItem( 10, TitleHealth        );
        AgentSessionTableWidget->horizontalHeader()->resizeSection( 5, 150 );


        AgentSessionTableWidget->setEnabled( true );
        AgentSessionTableWidget->horizontalHeader()->setVisible( true );
        AgentSessionTableWidget->setWordWrap( true );

        AgentSessionTableWidget->setShowGrid( false );
        AgentSessionTableWidget->setSortingEnabled( false );
        AgentSessionTableWidget->horizontalHeader()->setStretchLastSection( true );
        AgentSessionTableWidget->setSelectionBehavior( QAbstractItemView::SelectRows );
        AgentSessionTableWidget->setCornerButtonEnabled( true );
        AgentSessionTableWidget->setContextMenuPolicy( Qt::CustomContextMenu );
        AgentSessionTableWidget->verticalHeader()->setVisible( false );
        AgentSessionTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        //AgentSessionTableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeMode::Stretch );
        AgentSessionTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // The below code sets the first column (Icon box) to a fixed image and sets the rest of the columns to stretch the table.
        AgentSessionTableWidget->setColumnWidth(0, 40);
        for (int i = 1; i < 11; ++i) {
            AgentSessionTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        }

        connect(AgentSessionTableWidget, &QTableWidget::itemClicked, this, &AgentSessionTable::handleItemClicked);
    }


    void AgentSessionTable::handleItemClicked(QTableWidgetItem *item) {
        if (item) {
            GlobalUI::GlobalAgentCommanderTab->AddAgentTab(GlobalState::Agents[item->row()].Id); // The -1 is ugly.
        }
    }


    void AgentSessionTable::AddAgentSessionToTable(Amethyst::Util::Agent agent) {

        auto AgentIcon   =    new QTableWidgetItem();
        auto AgentID     =    new QTableWidgetItem();
        auto External    =    new QTableWidgetItem();
        auto Internal    =    new QTableWidgetItem();
        auto User        =    new QTableWidgetItem();
        auto Computer    =    new QTableWidgetItem();
        auto WinVersion  =   new QTableWidgetItem();
        auto Process     =    new QTableWidgetItem();
        auto ProcessId   =    new QTableWidgetItem();
        auto Last        =    new QTableWidgetItem();
        auto Health      =    new QTableWidgetItem();

        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->insertRow ( GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->rowCount() );
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem   ( GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->rowCount()-1,
                           0,
                           new QTableWidgetItem());
        // TODO AS agent.Id-1 isn't a great way for long term existing servers as agents will likely expire and such forth. Figure a way to refactor this.
        AgentIcon->setIcon(QIcon("C:\\Users\\j4ck\\Documents\\Projects\\Amethyst\\client\\Assets\\windows.png"));
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(agent.Id-1, 0, AgentIcon );

        AgentID->setText( QVariant(agent.Id).toString() );
        AgentID->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(agent.Id-1, 1, AgentID );

        External->setText(agent.ExternalIp);
        External->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(agent.Id-1, 2, External);

        Internal->setText(agent.InternalIp);
        Internal->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(agent.Id-1, 3, Internal);

        User->setText( agent.Username );
        User->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(agent.Id - 1, 4, User );

        Computer->setText( agent.ComputerName );
        Computer->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(agent.Id - 1, 5, Computer );

        WinVersion->setText( agent.WindowsVersion );
        WinVersion->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(agent.Id- 1, 6, WinVersion );

        Process->setText(agent.ProcessName);
        Process->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(agent.Id-1, 7, Process);

        ProcessId->setText(QVariant(agent.Pid).toString());
        ProcessId->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(agent.Id-1, 8, ProcessId);

        Last->setText(QString::number(agent.LastCallHome) + "seconds");
        Last->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(agent.Id-1, 9, Last);

        Health->setText("Ok");
        Health->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(agent.Id-1, 10, Health);

        // TODO DO THIS. (TIMER) && AND FIX THE agent.Id above THAT's GFARABGE


        QTimer* timer = new QTimer(this);
        timer->start(1000); // Update every second
        connect(timer, &QTimer::timeout, this, [=] {
            GlobalState::Agents[agent.Id].LastCallHome +=1;
            Last->setText(QString::number(GlobalState::Agents[agent.Id].LastCallHome) + " seconds");
            //GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(agent.Id-1, 8, Last);
        });


        /*
        sleep->setText(QVariant(agent.Sleep).toString());
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem(GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->rowCount() -1, 9, sleep);
        */

        /*
        listener->setText( agent.Listener );
        GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->setItem( GlobalUI::GlobalAgentSessionTable->AgentSessionTableWidget->rowCount() - 1, 1, listener );
        */

    }





}