add_executable(frogger_desktop
        main.cpp
)

target_link_libraries(frogger_desktop PRIVATE frogger_core ${SDL3_LIBRARY} ${SDL3_TFF_LIBRARY})
target_include_directories(frogger_desktop PRIVATE ${SDL3_INCLUDE_DIR})
target_include_directories(frogger_desktop PRIVATE ${SDL3_TFF_INCLUDE_DIR})
target_include_directories(frogger_desktop PRIVATE ${CMAKE_SOURCE_DIR}/src2)

add_custom_command(TARGET frogger_desktop POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/SDL3-3.2.28/x86_64-w64-mingw32/bin/SDL3.dll"
        "$<TARGET_FILE_DIR:frogger_desktop>"
)

add_custom_command(TARGET frogger_desktop POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/SDL3_ttf-3.2.2/x86_64-w64-mingw32/bin/SDL3_ttf.dll"
        "$<TARGET_FILE_DIR:frogger_desktop>"
)