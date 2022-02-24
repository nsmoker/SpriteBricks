add_executable(test WIN32
        gameTest.cpp TestGame.h)

target_link_libraries(test LINK_PUBLIC engine)