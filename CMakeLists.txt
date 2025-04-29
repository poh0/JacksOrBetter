cmake_minimum_required(VERSION 3.28)
project(JacksOrBetter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

if(WIN32)
    add_compile_options(/W4)
endif()

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
    OVERRIDE_FIND_PACKAGE # SelbaWard uses find_package for sfml
    )
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(selbaward
    GIT_REPOSITORY https://github.com/Hapaxia/SelbaWard
    GIT_TAG master)
FetchContent_MakeAvailable(SelbaWard)


set(SOURCES
    src/main.cpp
    src/JacksOrBetter.cpp
    src/Card.cpp
    src/Deck.cpp
    src/ResourceManager.cpp
    src/HandEvaluator.cpp
    src/Game.cpp
    src/Hand.cpp
    src/Animation.cpp
    src/AnimationManager.cpp
    src/MoveBehavior.cpp
    src/RotationBehavior.cpp
    src/PushButton.cpp
)
add_executable(JacksOrBetter ${SOURCES})

target_link_libraries(JacksOrBetter PRIVATE SFML::Graphics SFML::Audio SelbaWard)