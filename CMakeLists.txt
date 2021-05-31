cmake_minimum_required(VERSION 3.10)

project(alphabetloop_game)
SET(CMAKE_CXX_COMPILER clang++)


file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wall -lncursesw -g")

# copy config to build directory
configure_file(config.cfg ./
                   @ONLY)


add_executable(alphabetloop_game ${SOURCES})
target_include_directories(alphabetloop_game PRIVATE headers/)
