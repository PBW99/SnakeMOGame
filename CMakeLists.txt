#https://stackoverflow.com/questions/43772887/cmake-creating-a-static-library
cmake_minimum_required(VERSION 3.10)
project(SnakeMOGame)

set(CMAKE_CXX_STANDARD 11)

include_directories(Snake)
include_directories(SnakeClient)
include_directories(SnakeServer)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_library(Snake
        Snake/Console.cpp
        Snake/Console.h
        Snake/ConsoleBuffer.cpp
        Snake/ConsoleBuffer.h
        Snake/Context.cpp
        Snake/Context.h
        Snake/Food.cpp
        Snake/Food.h
        Snake/GameObject.cpp
        Snake/GameObject.h
        Snake/GameObjectRegistry.cpp
        Snake/GameObjectRegistry.h
        Snake/InputState.cpp
        Snake/InputState.h
        Snake/MemoryBitStream.cpp
        Snake/MemoryBitStream.h
        Snake/Move.cpp
        Snake/Move.h
        Snake/MoveList.cpp
        Snake/MoveList.h
        Snake/NetworkManager.cpp
        Snake/NetworkManager.h
        Snake/ObjectManager.cpp
        Snake/ObjectManager.h
        Snake/ReplicationCommand.h
        Snake/ScoreBoardManager.cpp
        Snake/ScoreBoardManager.h
        Snake/Snake.cpp
        Snake/Snake.h
        Snake/SnakePCH.h
        Snake/SnakeShared.h
        Snake/SocketAddress.cpp
        Snake/SocketAddress.h
        Snake/SocketAddressFactory.cpp
        Snake/SocketAddressFactory.h
        Snake/SocketUtil.cpp
        Snake/SocketUtil.h
        Snake/StringUtils.cpp
        Snake/StringUtils.h
        Snake/TCPSocket.cpp
        Snake/TCPSocket.h
        Snake/Timing.cpp
        Snake/Timing.h
        Snake/UDPSocket.cpp
        Snake/UDPSocket.h
        Snake/UtilMath.cpp
        Snake/UtilMath.h
        Snake/WeightedTimedMovingAverage.h
        Snake/World.cpp
        Snake/World.h
        )


add_executable(SnakeClient
        SnakeClient/Client.cpp
        SnakeClient/Client.h
        SnakeClient/FoodClient.cpp
        SnakeClient/FoodClient.h
        SnakeClient/InputManager.cpp
        SnakeClient/InputManager.h
        SnakeClient/main.cpp
        SnakeClient/NetworkManagerClient.cpp
        SnakeClient/NetworkManagerClient.h
        SnakeClient/RenderManager.cpp
        SnakeClient/RenderManager.h
        SnakeClient/ReplicationManagerClient.cpp
        SnakeClient/ReplicationManagerClient.h
        SnakeClient/SnakeClient.cpp
        SnakeClient/SnakeClient.h
        SnakeClient/SnakeClientPCH.h
        )
target_link_libraries(SnakeClient Snake)
target_link_libraries(SnakeClient ${CURSES_LIBRARIES})

add_executable(SnakeServer
        SnakeServer/ClientProxy.cpp
        SnakeServer/ClientProxy.h
        SnakeServer/DebugPrint.cpp
        SnakeServer/DebugPrint.h
        SnakeServer/FoodManager.cpp
        SnakeServer/FoodManager.h
        SnakeServer/FoodServer.cpp
        SnakeServer/FoodServer.h
        SnakeServer/main.cpp
        SnakeServer/NetworkManagerServer.cpp
        SnakeServer/NetworkManagerServer.h
        SnakeServer/ReplicationManagerServer.cpp
        SnakeServer/ReplicationManagerServer.h
        SnakeServer/Server.cpp
        SnakeServer/Server.h
        SnakeServer/SnakeServer.cpp
        SnakeServer/SnakeServer.h
        SnakeServer/SnakeServerPCH.h
        )
target_link_libraries(SnakeServer Snake)
