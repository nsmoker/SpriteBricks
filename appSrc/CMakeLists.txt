add_executable(test WIN32
        SpriteRenderer.h
        SpriteRenderer.cpp
        PlayerController.h
        PlayerController.cpp
        nyoom.h
        gameTest.cpp TestGame.h)

target_link_libraries(test LINK_PUBLIC engine)