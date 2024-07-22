//
// Created by j4ck on 3/20/24.
//
#include "../../../Include/Amethyst/Widgets/AgentCommanderTab.h"
#include "../../../Include/Amethyst/Utils/CommandParser.h"
#include "../../../Include/Amethyst/Controller.h"
#include "../../../Amethyst.h"
#include <QGridLayout>
#include <QDebug>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QScrollBar>

namespace Amethyst::Widgets {
    void AgentCommanderTab::Setup(QWidget* parent) {
        QGridLayout* GridLayout = new QGridLayout(parent); // This is required for stretch
        AgentCommanderTabWidget = new QTabWidget(parent);

        /* Create Event Viewer Tab Widget */
        QWidget* page = new QWidget();
        QVBoxLayout *tabLayout = new QVBoxLayout();
        GridLayout->addWidget(AgentCommanderTabWidget);
        EventViewerOutputTextEdit = new QTextEdit();
        EventViewerOutputTextEdit->setReadOnly(true);

        page->setLayout(tabLayout);
        tabLayout->addWidget(EventViewerOutputTextEdit);
        AgentCommanderTabWidget->addTab(page, "Event Viewer");
        AgentCommanderTabWidget->setTabsClosable(true);
    }

    void AgentCommanderTab::AddAgentTab(int agentId) {

        /* Setup New tab widgets */
        QWidget* page = new QWidget();
        QVBoxLayout *tabLayout = new QVBoxLayout();
        /* Setup Text Edit Command History */
        QTextEdit* outputTextEdit = new QTextEdit();
        outputTextEdit->setReadOnly(true);
        outputTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        QWidget* commandInputWidget = new QWidget();
        QHBoxLayout* hboxCommandInput = new QHBoxLayout(commandInputWidget);
        QLineEdit* commandLineEdit = new QLineEdit();
        QPushButton* inputCommandButton = new QPushButton("Execute");
        hboxCommandInput->addWidget(commandLineEdit);
        hboxCommandInput->addWidget(inputCommandButton);

        /* AgentCommandOutputWidgets is a list of TextEdits that keeps track of each Agent*/
        AgentCommandOutputTextEditWidgets.append(outputTextEdit);
        QString newCommandHistory;
        CommandHistoryList.append(newCommandHistory);

        /* Add Layout & Widgets to Page */
        page->setLayout(tabLayout);

        tabLayout->addWidget(outputTextEdit);
        tabLayout->addWidget(commandInputWidget);

        /* Handle Command Input - Button Click & Enter Cliccked */
        connect(inputCommandButton, &QPushButton::clicked, this, [=]() {
            HandleCommandEntered(agentId, commandLineEdit, outputTextEdit);
        });
        connect(commandLineEdit, &QLineEdit::returnPressed, this, [=]() {
            HandleCommandEntered(agentId, commandLineEdit, outputTextEdit);
        });


        //TODO FIX THIS
        QString tabName = GlobalState::Agents[GlobalState::Agents.size()-1].ComputerName + "\\" + GlobalState::Agents[GlobalState::Agents.size()-1].Username;
        AgentCommanderTabWidget->addTab(page, tabName);
    }

    void AgentCommanderTab::UpdateCommandHistory(int agentId, QString output) {
        CommandHistoryList[agentId-1] += output;
        AgentCommandOutputTextEditWidgets[agentId-1]->setHtml(CommandHistoryList[agentId-1]);

        // Get the vertical scrollbar of the QTextEdit
        QScrollBar *scrollBar = AgentCommandOutputTextEditWidgets[agentId-1]->verticalScrollBar();
        QTextCursor prev_cursor = AgentCommandOutputTextEditWidgets[agentId-1]->textCursor();
        AgentCommandOutputTextEditWidgets[agentId-1]->moveCursor (QTextCursor::End);
        AgentCommandOutputTextEditWidgets[agentId-1]->setTextCursor (prev_cursor);

// Set the scrollbar value to its maximum to move to the end
        scrollBar->setValue(scrollBar->maximum());
    }

    void AgentCommanderTab::UpdateEventViewerHistory(QString output) {
        EventViewerHistory += output;
        EventViewerOutputTextEdit->document()->setHtml(EventViewerHistory);
    }


    // Private
    void AgentCommanderTab::HandleCommandEntered(int agentId, QLineEdit* commandLineEdit, QTextEdit* outputTextEdit) {
        /* Update Command History Text Edit */
        QString agentName = "<font color=\"#66FF00\">" + GlobalState::Agents[GlobalState::Agents.size()-1].ComputerName  + "</font><font color=\"red\">\\</font><font color=\"#66FF00\">" + GlobalState::Agents[GlobalState::Agents.size()-1].Username + "> </font>";
        CommandHistoryList[agentId-1] = CommandHistoryList[agentId-1] + agentName + commandLineEdit->text() + "<br>";
        //CommandHistoryList[agentId-1] = CommandHistoryList[agentId-1] + "<br> <font color=\"#66FF00\">agent></font> " + commandLineEdit->text() + "<br>";
        /* Dispatch Command */
        Util::CommandParser(agentId, commandLineEdit->text());
        commandLineEdit->setText("");



    }
}
