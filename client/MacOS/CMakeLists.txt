cmake_minimum_required(VERSION 3.27)
project(client)

set(CMAKE_CXX_STANDARD 14)

# Linux
#set(Qt6_DIR "~/Qt/6.5.3/gcc_64/lib/cmake/Qt6")

#MacOS (Setting Qt6_DIR on Arm64 is a known bug  https://bugreports.qt.io/browse/QTBUG-97615)
#set(Qt6_DIR "~/Qt/6.7.2/macos/lib/cmake/Qt6")

set (SOURCES
        main.cpp
        Src/Amethyst/AppManager.cpp
        Src/Amethyst/MainWindow.cpp
        Src/Amethyst/Widgets/AgentSessionTable.cpp
        Src/Amethyst/Utils/Json.cpp
        Src/Amethyst/SocketHandler.cpp
        Src/Amethyst/Controller.cpp
        Amethyst.cpp
        Src/Amethyst/Widgets/AgentCommanderTab.cpp
        Src/Amethyst/Utils/CommandParser.cpp
        Src/Amethyst/Screens/AgentScreen.cpp
        Src/Amethyst/Screens/ListenerScreen.cpp
        Src/Amethyst/Widgets/ListenerTable.cpp
        Src/Amethyst/Dialogs/ListenerDialog.cpp
        Src/Amethyst/Screens/BuilderScreen.cpp
)

set (HEADERS
        Amethyst.h
        Include/Amethyst/AppManager.h
        Include/Amethyst/MainWindow.h
        Include/Amethyst/Widgets/AgentSessionTable.h
        Include/Amethyst/Utils/Json.h
        Include/Amethyst/Controller.h
        Include/Amethyst/SocketHandler.h
        Include/Amethyst/Widgets/AgentCommanderTab.h
        Include/Amethyst/Screens/AgentScreen.h
        Include/Amethyst/Utils/CommandParser.h
        Include/Amethyst/Utils/Json.h
        Include/Amethyst/Widgets/ListenerTable.h
        Include/Amethyst/Screens/ListenerScreen.h
        Include/Amethyst/Screens/BuilderScreen.h
        Include/Amethyst/Dialogs/ListenerDialog.h
)

#find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
#find_package(Qt6 REQUIRED COMPONENTS Network)
#find_package(Qt6 REQUIRED COMPONENTS WebSockets)


#include_directories("/Users/j4ck/Qt/6.7.2/macos/lib/QtWidgets.framework/Versions/A/Headers/qtwidgetsglobal.h")
#include_directories("/Users/j4ck/Qt/6.7.2/macos/include")
#include_directories("/Users/j4ck/Qt/6.7.2/macos/lib/QtWidgets.framework/Versions/A/Headers/")
#include_directories("/Users/j4ck/Qt/6.7.2/macos/lib/QtCore.framework/QtCore")
#include_directories("/Users/j4ck/Qt/6.7.2/macos/lib/QtCore.framework/Versions/A/Headers/")
#include_directories("/Users/j4ck/Qt/6.7.2/macos/lib/QtWidgets.framework/Versions/A/Headers/")
#include_directories("/Users/j4ck/Qt/6.7.2/macos/lib/QtCore.framework/Versions/A/Headers/")


#QT6_WRAP_CPP(MOC_SOURCES ${HEADERS})

#target_link_libraries(client Qt6::Core Qt6::Widgets Qt6::Network Qt6::WebSockets)
