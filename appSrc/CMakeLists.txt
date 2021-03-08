add_executable(test
        gameTest.cpp TestGame.h)

target_link_libraries(test LINK_PUBLIC engine)