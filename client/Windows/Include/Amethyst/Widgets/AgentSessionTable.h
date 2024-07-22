//
// Created by j4ck on 3/18/24.
//

#ifndef CLIENT_AGENTSESSIONTABLE_H
#define CLIENT_AGENTSESSIONTABLE_H
#include <QWidget>
#include <QPoint>
#include <QTableWidget>
#include <QContextMenuEvent>
#include "../../../Amethyst.h"

namespace Amethyst::Widgets {
    class AgentSessionTable : public QWidget
    {
        Q_OBJECT

    public:


        QTableWidget* AgentSessionTableWidget = nullptr;
        void Setup(QWidget* MainWidget);
        void AddAgentSessionToTable(Amethyst::Util::Agent agent);

    private:
        QTableWidgetItem*   TitleAgentIcon          = nullptr;
        QTableWidgetItem*   TitleAgentID            = nullptr;
        QTableWidgetItem*   TitleInternal           = nullptr;
        QTableWidgetItem*   TitleExternal           = nullptr;
        QTableWidgetItem*   TitleUser               = nullptr;
        QTableWidgetItem*   TitleComputer           = nullptr;
        QTableWidgetItem*   TitleWinVersion         = nullptr;
        QTableWidgetItem*   TitleProcess            = nullptr;
        QTableWidgetItem*   TitleProcessId          = nullptr;
        QTableWidgetItem*   TitleArch               = nullptr;
        QTableWidgetItem*   TitleLast               = nullptr;
        QTableWidgetItem*   TitleHealth             = nullptr;

    private slots:
        void handleItemClicked(QTableWidgetItem *item);
    };
}


#endif //CLIENT_AGENTSESSIONTABLE_H
