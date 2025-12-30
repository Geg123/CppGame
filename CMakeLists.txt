cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project(CppGame)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(ALUT_LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/alut.lib")
set(OPENAL_LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/OpenAL32.lib")
set(OPENAL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include/OpenAl")
set(INLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(TIMES_FONT "${CMAKE_CURRENT_SOURCE_DIR}/times.ttf")

set(ALUT_DLL "${CMAKE_CURRENT_SOURCE_DIR}/lib/alut.dll")

set(SDLTTF_VENDORED ON)
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

add_executable(main 
    main.cpp 
    src/Sprite.cpp
    src/Object.cpp
    src/logic.cpp
    src/lineal_alg.cpp
    src/graphics.cpp
    src/audio.cpp
    src/geometry.cpp
)

# Link to the actual SDL3 library.
target_link_libraries(main SDL3::SDL3 ${ALUT_LIB} ${OPENAL_LIB} SDL3_ttf::SDL3_ttf)
target_include_directories(main PRIVATE ${OPENAL_INCLUDE_DIRS} ${INLUDE_DIR})
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${ALUT_DLL}"
        "$<TARGET_FILE_DIR:main>"
    COMMENT "Copying alut.dll to output directory"
)
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${TIMES_FONT}"
        "$<TARGET_FILE_DIR:main>"
    COMMENT "Copying times.ttf to output directory"
)