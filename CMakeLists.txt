cmake_minimum_required(VERSION 3.10)
project(GreedySnakeC C)

set(CMAKE_C_STANDARD 99)

# Add compiler flags to ignore warnings
if(MSVC)
    add_compile_options(/W0)
endif()

# Windows specific configuration
if(WIN32)
    # For Windows, we'll use PDCurses
    set(PDCURSES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PDCurses)
    set(PDCURSES_INCLUDE_DIR ${PDCURSES_DIR})
    
    # Add PDCurses source files (pdcurses and wincon)
    file(GLOB PDCURSES_SOURCES 
        "${PDCURSES_DIR}/pdcurses/*.c"
        "${PDCURSES_DIR}/wincon/*.c"
    )
    
    # Create PDCurses library
    add_library(pdcurses STATIC ${PDCURSES_SOURCES})
    target_include_directories(pdcurses PUBLIC ${PDCURSES_INCLUDE_DIR})
    target_compile_definitions(pdcurses PRIVATE PDC_WIDE)
    set(CURSES_LIBRARIES pdcurses)
    set(CURSES_INCLUDE_DIRS ${PDCURSES_INCLUDE_DIR})
else()
    # For Unix-like systems
    find_package(Curses REQUIRED)
endif()

# Add your source files
add_executable(GreedySnake 
    src/main.c
    src/snake.c
    src/food.c
    src/game.c
    src/ui.c
    src/input.c
)

# Link ncurses to your executable
target_link_libraries(GreedySnake ${CURSES_LIBRARIES})

# Include header directory
target_include_directories(GreedySnake PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CURSES_INCLUDE_DIRS}
)