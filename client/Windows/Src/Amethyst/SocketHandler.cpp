//
// Created by j4ck on 3/20/24.
//
#include "../../Include/Amethyst/SocketHandler.h"
#include "../../Include/Amethyst/Controller.h"
#include "../../Amethyst.h"
#include <QDebug>
#include <QJsonDocument>
#include <QByteArray>

using namespace Amethyst;
SocketHandler::SocketHandler() {
    // TODO Get socket information and everything else important. (THIS IS JUST FOR DEV I WILL MOVE THIS LATER TO LOGIN)
    GlobalState::SocketConnection = new QWebSocket();
    //GlobalState::GlobalController = Controller = new Amethyst::Controller();
    //GlobalState::SocketConnection = webSocket;

    GlobalState::SocketConnection->open(QUrl("ws://127.0.0.1:9998/amethyst-operator"));

    // Web Socket Slots
    QObject::connect( GlobalState::SocketConnection, &QWebSocket::binaryMessageReceived, this, [&]( const QByteArray& Message )
    {
        // Send message to controller
        qDebug() << "New Message Received: " << Message;
        GlobalState::GlobalController->PacketReceiver(Message);
    });
    QObject::connect( GlobalState::SocketConnection, &QWebSocket::connected, this, [&]()
    {
        //TODO Send Login info. sendBinaryMessage. Then initialize. (Will be DB in future.):: Fetch from DB -> Cache to Global State.
    });
    QObject::connect( GlobalState::SocketConnection, &QWebSocket::disconnected, this, [&]()
    {
        qDebug() << "Socket Disconnected";
    });
}

// Destructor
SocketHandler::~SocketHandler() {

}