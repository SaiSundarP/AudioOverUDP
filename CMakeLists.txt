cmake_minimum_required(VERSION 3.16)
project(AudioUDP
    VERSION 0.0.1
    LANGUAGES C
)

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

include_directories(include)

add_executable(audio_sender
    src/sender.c
    src/udp.c
    src/audio.c
)

add_executable(audio_receiver
    src/receiver.c
    src/udp.c
)