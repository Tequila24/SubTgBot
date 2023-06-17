cmake_minimum_required(VERSION 3.5)

project(Sub-tg-bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(fmt REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

include_directories(./modules/)
include_directories(./)

add_executable(Sub-tg-bot main.cpp
    logging.h logging.cpp
    messagehandler.h messagehandler.cpp
    jsonutils.h jsonutils.cpp
    ./modules/pimodule.h ./modules/pimodule.cpp
    StringUtils.h)

target_link_libraries(Sub-tg-bot /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES} fmt::fmt)
