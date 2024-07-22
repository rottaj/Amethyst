//
// Created by j4ck on 3/17/24.
//

#ifndef CLIENT_APPMANAGER_H
#define CLIENT_APPMANAGER_H

#include "SocketHandler.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QWebSocket>

namespace Amethyst{
    class AppManager {
    public:

        QMainWindow* RealStealMainWindow;
        Amethyst::SocketHandler* SocketHandler;


        AppManager(); // initializer
        void Init(int argc, char** argv);

        void StartUserInterface();

        ~AppManager();// Destructor
    private:

    };
}


#endif //CLIENT_APPMANAGER_H
