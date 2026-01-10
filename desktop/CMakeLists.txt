add_executable(frogger_desktop
        main2.cpp
)
add_executable(frogger_desktop_2
        main.cpp
)

target_link_libraries(frogger_desktop PRIVATE frogger_core ${SDL3_LIBRARY})
target_include_directories(frogger_desktop PRIVATE ${SDL3_INCLUDE_DIR})

target_link_libraries(frogger_desktop_2 PRIVATE frogger_core2 ${SDL3_LIBRARY} ${SDL3_TFF_LIBRARY})
target_include_directories(frogger_desktop_2 PRIVATE ${SDL3_INCLUDE_DIR})
target_include_directories(frogger_desktop_2 PRIVATE ${SDL3_TFF_INCLUDE_DIR})
target_include_directories(frogger_desktop_2 PRIVATE ${CMAKE_SOURCE_DIR}/src2)