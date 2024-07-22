//
// Created by j4ck on 3/17/24.
//

#ifndef CLIENT_MAINWINDOW_H
#define CLIENT_MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QWidget>
#include <QSplitter>
#include <QGridLayout>
#include "Widgets/AgentSessionTable.h"


namespace Amethyst {
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = nullptr); // This is the Main Window (called in MainWindow::MainWindow() in MainWindow.cpp)

        QWidget*                CentralWidget;
        QHBoxLayout*            MainGridLayout;
        QStackedWidget*         MainStackedWidget;
        QWidget*                AmethystSideBarMenuWidget;
        QVBoxLayout*            AmethystSideBarMenuLayout;

        QWidget*                AmethystAgentMenuWidget;

        QVBoxLayout*            AmethystAgentMenuLayout;

        ~MainWindow() override; // Destructor

    private:
        void Setup(QWidget* parent);
        // Add at least one virtual function declaration

    };
}

#endif //CLIENT_MAINWINDOW_H
