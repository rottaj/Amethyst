//
// Created by j4ck on 3/16/24.
//
#include <QApplication>
#include "Amethyst.h"
#include "./Include/Amethyst/AppManager.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Amethyst::AppManager appManager;
    appManager.StartUserInterface(); // Fix this. MainUI will be set to false until socket connection is established.
    appManager.Init(argc, argv);

    return app.exec();
}
