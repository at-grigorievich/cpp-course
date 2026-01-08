cmake_minimum_required(VERSION 3.15)
project(BankSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BankSystem
    banking-system.cpp

    Client.cpp
    PremiumClient.cpp

    Account.cpp
    Transaction.cpp
    Bank.cpp
)

target_include_directories(BankSystem PRIVATE
    include
)

if (MSVC)
    target_compile_options(BankSystem PRIVATE /W4)
else()
    target_compile_options(BankSystem PRIVATE -Wall -Wextra -Wpedantic)
endif()
