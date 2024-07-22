//
// Created by j4ck on 3/20/24.
//

#ifndef CLIENT_AGENTCOMMANDERTAB_H
#define CLIENT_AGENTCOMMANDERTAB_H

#include <QWidget>
#include <QString>
#include <QTabWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVector>
#include "../../../Amethyst.h"

namespace Amethyst::Widgets {
    class AgentCommanderTab : public QWidget
    {
        Q_OBJECT

    public:


        QTabWidget* AgentCommanderTabWidget = nullptr;
        void Setup(QWidget* MainWidget);
        void AddAgentTab(int agentId);
        void UpdateCommandHistory(int agentId, QString output);
        void UpdateEventViewerHistory(QString output);
        QString                         EventViewerHistory;
        QVector<QString>                CommandHistoryList;
        QTextEdit*                      EventViewerOutputTextEdit;
        QVector<QTextEdit*>             AgentCommandOutputTextEditWidgets;

    private:
        void HandleCommandEntered(int agentId, QLineEdit* commandLineEdit, QTextEdit* outputTextEdit);
    };
}



#endif //CLIENT_AGENTCOMMANDERTAB_H
