cmake_minimum_required(VERSION 3.28)
project(JacksOrBetter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

if(WIN32)
    add_compile_options(/W4)
endif()

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(SOURCES
    src/main.cpp
    src/JacksOrBetter.cpp
    src/Card.cpp
    src/Deck.cpp
    src/ResourceManager.cpp
    src/HandEvaluator.cpp
)
add_executable(JacksOrBetter ${SOURCES})

target_link_libraries(JacksOrBetter PRIVATE SFML::Graphics)