cmake_minimum_required(VERSION 4.1)
project(depths-of-kaeldrath)

set(CMAKE_CXX_STANDARD 20)

add_executable(depths-of-kaeldrath main.cpp
        Item.cpp
        Item.h
        Player.cpp
        Player.h
        Enemy.cpp
        Enemy.h
        Scene.cpp
        Scene.h
        PuzzleScene.cpp
        PuzzleScene.h
        ItemScene.cpp
        ItemScene.h
        CombatScene.cpp
        CombatScene.h
        GameManager.cpp
        GameManager.h
        SaveManager.cpp
        SaveManager.h
        LockedDoorScene.cpp
        LockedDoorScene.h)