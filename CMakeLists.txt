cmake_minimum_required(VERSION 3.9)
project(BShip)

set(CMAKE_CXX_STANDARD 11)

add_executable(BShip main.cpp #[[BShip/BShipGame.cpp BShip/BShipGame.h]] BShip/BShipGrid.cpp BShip/BShipGrid.h #[[BShip/BShip.cpp BShip/BShip.h BShip/BShipFacts.cpp BShip/BShipFacts.h BShip/BShipController.cpp BShip/BShipController.h BShip/UserController.cpp BShip/UserController.h BShip/CPUController.cpp BShip/CPUController.h]] BShip/BShipGridSpot.h)