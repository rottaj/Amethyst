//
// Created by j4ck on 4/7/24.
//

#ifndef CLIENT_LISTENERTABLE_H
#define CLIENT_LISTENERTABLE_H
#include <QWidget>
#include <QPoint>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QContextMenuEvent>
#include "../../../Amethyst.h"

namespace Amethyst::Widgets {
    class ListenerTable : public QWidget
    {
    Q_OBJECT

    public:


        QTableWidget* ListenerTableWidget = nullptr;
        void Setup(QWidget* MainWidget);
        void AddListenerToListenerTable(Amethyst::Util::Listener listener);

    private:
        QTableWidgetItem*   TitleListenerID        = nullptr;
        QTableWidgetItem*   TitleListenerName        = nullptr;
        QTableWidgetItem*   TitleListenerHost        = nullptr;
        QTableWidgetItem*   TitleListenerPort        = nullptr;
        QTableWidgetItem*   TitleListenerUri        = nullptr;

    private slots:
        //void handleItemClicked(QTableWidgetItem *item);
    };
}


#endif //CLIENT_LISTENERTABLE_H
