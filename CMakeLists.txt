cmake_minimum_required(VERSION 3.22.1)
project(scanner)

set(SOURCES src/main.c src/reader.c src/jpeg.c)

add_executable(scanner ${SOURCES})

target_include_directories(scanner PRIVATE ${PROJECT_SOURCE_DIR}/include)