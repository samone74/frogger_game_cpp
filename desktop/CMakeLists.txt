add_executable(frogger_desktop
        main.cpp
)

target_link_libraries(frogger_desktop PRIVATE frogger_core ${SDL3_LIBRARY} ${SDL3_TFF_LIBRARY})
target_include_directories(frogger_desktop PRIVATE ${SDL3_INCLUDE_DIR})
target_include_directories(frogger_desktop PRIVATE ${SDL3_TFF_INCLUDE_DIR})
target_include_directories(frogger_desktop PRIVATE ${CMAKE_SOURCE_DIR}/src2)