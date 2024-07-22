//
// Created by j4ck on 4/7/24.
//
#include "../../../Include/Amethyst/Widgets/ListenerTable.h"
#include "../../../Amethyst.h"
#include <QTimer>
#include <QHeaderView>
#include <QObject>
#include <QAbstractItemView>
#include <QSize>
#include <QMenu>
#include <QSizePolicy>
#include <QGridLayout>
#include <QTableWidget>
#include <QAction>

namespace Amethyst::Widgets {
    void ListenerTable::Setup(QWidget *parent) {

        QGridLayout *GridLayout = new QGridLayout(parent); // This is required for stretch
        ListenerTableWidget = new QTableWidget(parent);
        GridLayout->addWidget(ListenerTableWidget);
        //ListenerTableWidget->setStyleSheet("background-color: blue;");
        ListenerTableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        ListenerTableWidget->setColumnCount(5);
        ListenerTableWidget->setRowCount(4); // Set the number of columns as required
        ListenerTableWidget->setStyleSheet("QTableView::item { border: 1px solid black; }");


        /* Beginning of Table Builder */
        TitleListenerID = new QTableWidgetItem(     "ID"        );
        TitleListenerName = new QTableWidgetItem(   "Name"      );
        TitleListenerHost = new QTableWidgetItem(   "Host"      );
        TitleListenerPort = new QTableWidgetItem(   "Port"      );
        TitleListenerUri = new QTableWidgetItem(    "Uri"       );



        ListenerTableWidget->setHorizontalHeaderItem( 0, TitleListenerID         );
        ListenerTableWidget->setHorizontalHeaderItem( 1, TitleListenerName       );
        ListenerTableWidget->setHorizontalHeaderItem( 2, TitleListenerHost       );
        ListenerTableWidget->setHorizontalHeaderItem( 3, TitleListenerPort       );
        ListenerTableWidget->setHorizontalHeaderItem( 4, TitleListenerUri       );


        ListenerTableWidget->setEnabled( true );
        ListenerTableWidget->horizontalHeader()->setVisible( true );
        ListenerTableWidget->setWordWrap( true );
        ListenerTableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeMode::Stretch );

        ListenerTableWidget->setShowGrid( false );
        ListenerTableWidget->setSortingEnabled( false );
        ListenerTableWidget->horizontalHeader()->setStretchLastSection( true );
        ListenerTableWidget->setSelectionBehavior( QAbstractItemView::SelectRows );
        ListenerTableWidget->setCornerButtonEnabled( true );
        ListenerTableWidget->setContextMenuPolicy( Qt::CustomContextMenu );
        ListenerTableWidget->verticalHeader()->setVisible( false );
        ListenerTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ListenerTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ListenerTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        ListenerTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    void ListenerTable::AddListenerToListenerTable(Amethyst::Util::Listener listener) {
        auto ListenerID     =    new QTableWidgetItem();
        auto Name           =    new QTableWidgetItem();
        auto Host           =    new QTableWidgetItem();
        auto Port           =    new QTableWidgetItem();
        auto Uri            =    new QTableWidgetItem();
        GlobalUI::GlobalListenerTable->ListenerTableWidget->insertRow ( GlobalUI::GlobalListenerTable->ListenerTableWidget->rowCount() );
        GlobalUI::GlobalListenerTable->ListenerTableWidget->setItem   ( GlobalUI::GlobalListenerTable->ListenerTableWidget->rowCount()-1,
                                                                                0,
                                                                                new QTableWidgetItem());
        // TODO AS agent.Id-1 isn't a great way for long term existing servers as agents will likely expire and such forth. Figure a way to refactor this.
        ListenerID->setText( QVariant(listener.Id).toString() );
        GlobalUI::GlobalListenerTable->ListenerTableWidget->setItem(listener.Id-1, 0, ListenerID );
        Name->setText(listener.Name);
        GlobalUI::GlobalListenerTable->ListenerTableWidget->setItem(listener.Id-1, 1, Name );

        Host->setText(listener.Host);
        GlobalUI::GlobalListenerTable->ListenerTableWidget->setItem(listener.Id-1, 2, Host );

        Port->setText(QString::number(listener.Port));
        GlobalUI::GlobalListenerTable->ListenerTableWidget->setItem(listener.Id-1, 3, Port );

        Uri->setText(listener.Uri);
        GlobalUI::GlobalListenerTable->ListenerTableWidget->setItem(listener.Id-1, 4, Uri );


    }
}
