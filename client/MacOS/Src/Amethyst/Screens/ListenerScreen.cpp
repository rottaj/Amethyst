//
// Created by j4ck on 4/7/24.
//

#include "../../../Include/Amethyst/Screens/ListenerScreen.h"
#include "../../../Include/Amethyst/Widgets/ListenerTable.h"
#include "../../../Include/Amethyst/Dialogs/ListenerDialog.h"
#include <QObject>
#include <QPushButton>
#include <QSplitter>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QSizePolicy>

using namespace Amethyst::Widgets;

namespace Amethyst {
    void Screens::ListenerScreen::Setup() {
        ListenerScreenMainWidget = new QWidget();

        ListenerScreenMainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


        QWidget* ListenerTableContainer = new QWidget();
        //AgentTableContainer->setStyleSheet("background-color: red;");
        GlobalUI::GlobalListenerTable->Setup(ListenerTableContainer);

        QWidget* ListenerConfigurationWidget = new QWidget();
        QHBoxLayout* ListenerConfigurationLayout = new QHBoxLayout();
        QPushButton*  ListenerCreateButton = new QPushButton("Create");
        ListenerConfigurationLayout->addWidget(ListenerCreateButton);
        ListenerConfigurationWidget->setLayout(ListenerConfigurationLayout);

        connect(ListenerCreateButton, &QPushButton::clicked, this, [=]() {
            qDebug() << "Foobar";
            Amethyst::Dialogs::ListenerDialog* dialog = new Amethyst::Dialogs::ListenerDialog();
            dialog->setModal(true);
            dialog->show();
        });


        QSplitter* splitter = new QSplitter();

        splitter->addWidget(ListenerTableContainer);
        splitter->addWidget(ListenerConfigurationWidget);
        ListenerScreenLayout = new QVBoxLayout();
        ListenerScreenLayout->addWidget(splitter);
        splitter->setOrientation(Qt::Vertical);
        ListenerScreenMainWidget->setLayout(ListenerScreenLayout);
    }
}