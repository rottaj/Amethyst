//
// Created by j4ck on 4/18/24.
//

#ifndef CLIENT_BUILDERSCREEN_H
#define CLIENT_BUILDERSCREEN_H
#include "../../../Amethyst.h"
#include <QWidget>
#include <QVBoxLayout>

namespace Amethyst::Screens {
    class BuilderScreen  : public QWidget
    {
    Q_OBJECT

    public:

        QWidget*        BuilderScreenMainWidget;
        QVBoxLayout*    BuilderScreenLayout;
        void Setup(/*QWidget* Main*/);

    };
}
#endif //CLIENT_BUILDERSCREEN_H
