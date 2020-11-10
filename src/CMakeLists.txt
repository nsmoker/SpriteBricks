add_library(engine
    graphics/window.h
    graphics/window.cpp
    graphics/graphics.h
    graphics/graphicsDevice.cpp
    graphics/graphicsDevice.h
    graphics/shader.h
    graphics/shader.cpp
    graphics/material.h
    graphics/material.cpp
    graphics/batcher.cpp
    graphics/batcher.h

        math/rectangle.cpp math/rectangle.h input/InputManager.cpp input/InputManager.h)

cmake_policy(SET CMP0072 NEW)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(engine PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> 
    "$<BUILD_INTERFACE:${SDL2_INCLUDE_DIRS}>" "$<BUILD_INTERFACE:${SDL2_IMAGE_INCLUDE_DIRS}>"
    "$<BUILD_INTERFACE:${GLEW_INCLUDE_DIRS}>"
    "$<BUILD_INTERFACE:${OPENGL_INCLUDE_DIRS}>"
)

target_link_libraries(engine PUBLIC 
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
)