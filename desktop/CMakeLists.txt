
set(SDL3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/windows/SDL3-3.2.28/x86_64-w64-mingw32/include")
set(SDL3_LIBRARY "${CMAKE_SOURCE_DIR}/lib/windows/SDL3-3.2.28/x86_64-w64-mingw32/lib/libSDL3.dll.a") # or SDL3.a for MinGW
set(SDL3_TFF_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/windows/SDL3_ttf-3.2.2/x86_64-w64-mingw32/include")
set(SDL3_TFF_LIBRARY "${CMAKE_SOURCE_DIR}/lib/windows/SDL3_ttf-3.2.2/x86_64-w64-mingw32/lib/libSDL3_ttf.dll.a")
set(SDL3_IMAGE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/windows/SDL3_image-3.4.0/x86_64-w64-mingw32/include")
set(SDL3_image "${CMAKE_SOURCE_DIR}/lib/windows/SDL3_image-3.4.0/x86_64-w64-mingw32/lib/libSDL3_image.dll.a")

add_executable(frogger_desktop
        main.cpp
)

target_link_libraries(frogger_desktop PRIVATE frogger_core ${SDL3_LIBRARY} ${SDL3_TFF_LIBRARY} ${SDL3_image})
target_include_directories(frogger_desktop PRIVATE ${SDL3_INCLUDE_DIR})
target_include_directories(frogger_desktop PRIVATE ${SDL3_TFF_INCLUDE_DIR})
target_include_directories(frogger_desktop PRIVATE ${CMAKE_SOURCE_DIR}/src2)

target_include_directories(frogger_core PUBLIC
        ${SDL3_INCLUDE_DIR}
        ${SDL3_TFF_INCLUDE_DIR}
        ${SDL3_IMAGE_INCLUDE_DIR}
)

add_custom_command(TARGET frogger_desktop POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/windows/SDL3-3.2.28/x86_64-w64-mingw32/bin/SDL3.dll"
        "$<TARGET_FILE_DIR:frogger_desktop>"
)

add_custom_command(TARGET frogger_desktop POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/windows/SDL3_ttf-3.2.2/x86_64-w64-mingw32/bin/SDL3_ttf.dll"
        "$<TARGET_FILE_DIR:frogger_desktop>"
)

add_custom_command(TARGET frogger_desktop POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/lib/windows/SDL3_image-3.4.0/x86_64-w64-mingw32/bin/SDL3_image.dll"
        "$<TARGET_FILE_DIR:frogger_desktop>"
)

add_custom_command(TARGET frogger_desktop POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:frogger_desktop>/assets"
)
