//
// Created by j4ck on 4/18/24.
//
//

#include "../../../Include/Amethyst/Screens/BuilderScreen.h"
#include <QObject>
#include <QPushButton>
#include <QSplitter>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QTextEdit>
#include <QSizePolicy>

using namespace Amethyst::Widgets;

namespace Amethyst {
    void Screens::BuilderScreen::Setup() {
        BuilderScreenMainWidget = new QWidget();
        BuilderScreenLayout = new QVBoxLayout();
        BuilderScreenMainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


        QWidget* AgentBuilderBox = new QWidget();
        QVBoxLayout* AgentBuilderBoxLayout = new QVBoxLayout();

        QLabel* AgentBuilderBoxTitle = new QLabel("Agent Builder");
        AgentBuilderBoxLayout->addWidget(AgentBuilderBoxTitle);

        QLabel* AgentNameLabel = new QLabel("Agent name");
        QLineEdit* AgentNameLineEdit = new QLineEdit();
        AgentNameLineEdit->setText(QString("Agent 1"));
        AgentBuilderBoxLayout->addWidget(AgentNameLabel);
        AgentBuilderBoxLayout->addWidget(AgentNameLineEdit);

        QLabel* OutputFileLabel = new QLabel("Output file name");
        QLineEdit* OutputFileLineEdit = new QLineEdit();
        OutputFileLineEdit->setText(QString("agent.exe"));
        AgentBuilderBoxLayout->addWidget(OutputFileLabel);
        AgentBuilderBoxLayout->addWidget(OutputFileLineEdit);

        QPushButton* BuildAgentButton = new QPushButton("Build");
        AgentBuilderBoxLayout->addWidget(BuildAgentButton);


        QLabel* ConsoleTitle = new QLabel("Builder Console");
        QTextEdit* BuilderConsoleOutput = new QTextEdit();
        AgentBuilderBoxLayout->addWidget(ConsoleTitle);
        AgentBuilderBoxLayout->addWidget(BuilderConsoleOutput);

        AgentBuilderBox->setLayout(AgentBuilderBoxLayout);

        BuilderScreenLayout->addWidget(AgentBuilderBox);
        BuilderScreenMainWidget->setLayout(BuilderScreenLayout);

    }
}