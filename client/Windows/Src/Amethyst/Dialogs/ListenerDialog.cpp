//
// Created by j4ck on 4/7/24.
//
#include "../../../Include/Amethyst/Dialogs/ListenerDialog.h"
#include "../../../Include/Amethyst/Controller.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

using namespace Amethyst::Widgets;

namespace Amethyst {
    Dialogs::ListenerDialog::ListenerDialog() {

        QWidget* ListenerDialogMainWidget = new QWidget(this);

        QVBoxLayout* ListenerDialogMainLayout = new QVBoxLayout(this);
        ListenerDialogMainLayout->setAlignment(Qt::AlignTop);

        /* Listener Name */
        QLabel *ListenerNameLabel = new QLabel("Name", this);
        QLineEdit *ListenerNameLineEdit = new QLineEdit(this);
        ListenerNameLineEdit->setText(QString("Amethyst Listener 1"));
        /* Listener Host */
        QLabel *ListenerHostLabel = new QLabel("Host", this);
        QLineEdit *ListenerHostLineEdit = new QLineEdit(this);
        ListenerHostLineEdit->setText(QString("172.16.7.1"));
        /* Listener Port */
        QLabel *ListenerPortLabel = new QLabel("Port", this);
        QLineEdit *ListenerPortLineEdit = new QLineEdit(this);
        ListenerPortLineEdit->setText(QString("80"));

        QLabel *ListenerUriLabel = new QLabel("Uri", this);
        QLineEdit *ListenerUriLineEdit = new QLineEdit(this);
        ListenerUriLineEdit->setText(QString("/default"));


        QWidget* ButtonBox = new QWidget(this);
        QHBoxLayout* ButtonBoxLayout = new QHBoxLayout();
        ButtonBox->setLayout(ButtonBoxLayout);

        QPushButton *ButtonSaveListener = new QPushButton("Save", this);
        QPushButton *ButtonCloseListener = new QPushButton("Close", this);

        ButtonBoxLayout->addWidget(ButtonSaveListener);
        ButtonBoxLayout->addWidget(ButtonCloseListener);

        // Connect close button signal to close slot
        connect(ButtonCloseListener, &QPushButton::clicked, this, &ListenerDialog::hide);
        connect(ButtonSaveListener, &QPushButton::clicked, this, [=]() {
            // Dispatch Listener Creation to Teamserver
            Amethyst::Util::Listener newListener = {0,
                                                    QString(ListenerNameLineEdit->text()),
                                                    QString(ListenerHostLineEdit->text()),
                                                    QString(ListenerPortLineEdit->text()).toInt(),
                                                    QString(ListenerUriLineEdit->text()),
                                                    };
            GlobalState::GlobalController->DispatchNewListener(newListener);
        });


        // Layout setup
        ListenerDialogMainLayout->addWidget(ListenerDialogMainWidget);

        ListenerDialogMainLayout->addWidget(ListenerNameLabel);
        ListenerDialogMainLayout->addWidget(ListenerNameLineEdit);

        ListenerDialogMainLayout->addWidget(ListenerHostLabel);
        ListenerDialogMainLayout->addWidget(ListenerHostLineEdit);

        ListenerDialogMainLayout->addWidget(ListenerPortLabel);
        ListenerDialogMainLayout->addWidget(ListenerPortLineEdit);

        ListenerDialogMainLayout->addWidget(ListenerUriLabel);
        ListenerDialogMainLayout->addWidget(ListenerUriLineEdit);

        ListenerDialogMainLayout->addWidget(ButtonBox);

        // Set layout for the dialog
        setLayout(ListenerDialogMainLayout);

        // Set dialog properties
        setWindowTitle("Configure Listener");
        setFixedSize(600, 800); // Fixed size, adjust as needed
    }
}

