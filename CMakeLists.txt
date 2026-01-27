cmake_minimum_required(VERSION 4.0)
project(InlamningAlgos_DesignPatterns C)

set(CMAKE_C_STANDARD 11)

include_directories(include
        src)


add_executable(InlamningAlgos_DesignPatterns
        main.c
        include/EventQueue.h
        include/EventLog.h
        include/Event.h
        include/EventProducer.h
        include/EventConsumer.h
        include/UserInterface.h
        include/TestHelpers.h
        src/EventQueue.c
        src/EventLog.c
        src/EventProducer.c
        src/EventConsumer.c
        src/UserInterface.c
        src/TestHelpers.c
        include/EventSort.h
        src/EventSort.c
)
