#include "../../Amethyst.h"
#include <QWebSocket>
#include <QUrl>

namespace Amethyst{
    class SocketHandler : public QTcpSocket {
    private:
        Amethyst::Controller* Controller;
    public:
        QWebSocket* SocketConnection;
        SocketHandler();
        ~SocketHandler();
    };
}