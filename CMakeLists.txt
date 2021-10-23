cmake_minimum_required(VERSION 3.20)
project(Wolfram_Automata)

set(CMAKE_CXX_STANDARD 14)

set(automata_dir Automata/wolfram_automata.h Automata/wolfram_automata.cpp
        )


set(sfml_dir
        sfml_window/window.h sfml_window/window.cpp
        sfml_window/coord.h sfml_window/coord.cpp
        sfml_window/color_scheme.h sfml_window/color_scheme.cpp
        sfml_window/slicer.h sfml_window/slicer.cpp
       )

add_executable(Wolfram_Automata WA_main.cpp
        ${automata_dir}
        ${sfml_dir}
        )

add_subdirectory(sfml)

set(executables Wolfram_Automata)

foreach(executable IN LISTS executables)
    target_include_directories(${executable}
            PUBLIC ${PROJECT_SOURCE_DIR}/sfml/include)
endforeach()

foreach(executable IN LISTS executables)
    target_link_directories(${executable}
            PUBLIC ${PROJECT_SOURCE_DIR}/sfml/src)
endforeach()

foreach(executable IN LISTS executables)
    target_link_libraries(${executable}
            sfml-graphics
            sfml-system
            sfml-window)
endforeach()
