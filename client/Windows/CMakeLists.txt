cmake_minimum_required(VERSION 3.27)
project(client)

set(CMAKE_CXX_STANDARD 14)

# Linux
#set(Qt6_DIR "~/Qt/6.5.3/gcc_64/lib/cmake/Qt6")

set(Qt6_DIR "C:\\Qt\\6.5.3\\mingw_64\\lib\\cmake")
#set(QT_QPA_PLATFORM_PLUGIN_PATH "C:\\Qt\\6.5.3\\mingw_64\\plugins\\platforms")

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

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)

# Linux
#include_directories("~/Qt/6.5.3/gcc_64/include/")
#include_directories("~/Qt/6.5.3/gcc_64/include/QtCore")

include_directories("C:\\Qt\\6.5.3\\mingw_64\\include")
include_directories("C:\\Qt\\6.5.3\\mingw_64\\include\\QtCore")


QT6_WRAP_CPP(MOC_SOURCES ${HEADERS})

add_executable(client ${SOURCES} ${MOC_SOURCES})

target_link_libraries(client Qt6::Core Qt6::Widgets Qt6::Network Qt6::WebSockets)
