cmake_minimum_required(VERSION 3.20)
project(src/GUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(PREPEND CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml@2")
find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

add_executable(GUI src/main.cpp)
target_link_libraries(GUI PRIVATE sfml-graphics sfml-window sfml-system)