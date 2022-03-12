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
    editor/Editor.h
    editor/Editor.cpp
    entity/Entity.h
    entity/Entity.cpp
    entity/Component.h
    entity/Transform.h
    external/stb_image.h
    entity/Transform.cpp
    external/json.hpp
    external/dear_imgui/imgui_demo.cpp
    external/dear_imgui/imgui_draw.cpp
    external/dear_imgui/imgui_impl_opengl3.cpp
    external/dear_imgui/imgui_impl_opengl3.h
    external/dear_imgui/imgui_impl_sdl.cpp
    external/dear_imgui/imgui_impl_sdl.h
    external/dear_imgui/imgui_internal.h
    external/dear_imgui/imgui_tables.cpp
    external/dear_imgui/imgui_widgets.cpp
    external/dear_imgui/imgui.cpp
    external/dear_imgui/imgui.h
    external/dear_imgui/imconfig.h
    external/dear_imgui/imgui_impl_opengl3_loader.h
    external/dear_imgui/imstb_rectpack.h
    external/dear_imgui/imstb_textedit.h
    external/dear_imgui/imstb_truetype.h
        math/rectangle.cpp
        math/rectangle.h
        math/vec.cpp
        math/vec.h
        input/InputManager.cpp input/InputManager.h texture/Texture.cpp texture/Texture.h game/game.cpp game/game.h)

cmake_policy(SET CMP0072 NEW)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

add_definitions(-DGLEW_STATIC)

target_include_directories(engine PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    "$<BUILD_INTERFACE:${SDL2_INCLUDE_DIRS}>" "$<BUILD_INTERFACE:${SDL2TTF_INCLUDE_DIRS}>"
    "$<BUILD_INTERFACE:${GLEW_INCLUDE_DIRS}>"
    "$<BUILD_INTERFACE:${OPENGL_INCLUDE_DIRS}>"
)

target_link_libraries(engine PUBLIC 
    ${SDL2_LIBRARIES} 
    ${SDL2TTF_LIBRARY}
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${CMAKE_DL_LIBS}
)