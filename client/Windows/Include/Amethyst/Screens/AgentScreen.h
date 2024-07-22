//
// Created by j4ck on 4/7/24.
//

#ifndef CLIENT_AGENTSCREEN_H
#define CLIENT_AGENTSCREEN_H
#include "../../../Amethyst.h"
#include <QWidget>
#include <QVBoxLayout>

namespace Amethyst::Screens {
    class AgentScreen{/*; : public QWidget
    {
        Q_OBJECT*/

    public:

        QWidget*        AgentScreenMainWidget;
        QVBoxLayout*    AgentScreenLayout;
        void Setup(/*QWidget* Main*/);

    };
}
#endif //CLIENT_AGENTSCREEN_H
