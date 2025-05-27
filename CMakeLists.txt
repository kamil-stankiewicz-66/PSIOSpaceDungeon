cmake_minimum_required(VERSION 3.16)

project(PSIOSpaceDungeon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SFML_ROOT ${PROJECT_SOURCE_DIR}/SFML-2.5.1/)
include_directories(${SFML_ROOT}/include)
link_directories(${SFML_ROOT}/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(PSIOSpaceDungeon main.cpp
    include/engine/core/Debuger.h
    include/engine/core/Engine.h
    include/engine/core/Vector2.h
    source/engine/core/Vector2.cpp
    source/engine/core/Engine.cpp
)

set_target_properties(
    PSIOSpaceDungeon PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/release"
)

include(GNUInstallDirs)
install(TARGETS PSIOSpaceDungeon
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(PSIOSpaceDungeon
    sfml-graphics
    sfml-window
    sfml-system
)
