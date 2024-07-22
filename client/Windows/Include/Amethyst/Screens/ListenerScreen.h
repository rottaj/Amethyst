//
// Created by j4ck on 4/7/24.
//

#ifndef CLIENT_LISTENERSCREEN_H
#define CLIENT_LISTENERSCREEN_H
#include "../../../Amethyst.h"
#include <QWidget>
#include <QVBoxLayout>

namespace Amethyst::Screens {
    class ListenerScreen  : public QWidget
    {
        Q_OBJECT

    public:

        QWidget*        ListenerScreenMainWidget;
        QVBoxLayout*    ListenerScreenLayout;
        void Setup(/*QWidget* Main*/);

    };
}
#endif //CLIENT_LISTENERSCREEN_H
