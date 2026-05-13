cmake_minimum_required(VERSION 3.10)
project(SFMLRunner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

# Add ALL source files
add_executable(SFMLRunner
    main.cpp

    PROJECT/GameEngine.cpp
    PROJECT/Player.cpp
    PROJECT/TrackManager.cpp
    PROJECT/ScoreManager.cpp
    PROJECT/Coin.cpp
    PROJECT/Obstacle.cpp
    PROJECT/PowerUp.cpp
)

# Include directory for headers
target_include_directories(SFMLRunner PUBLIC ${CMAKE_SOURCE_DIR}/PROJECT)

# Link SFML
target_link_libraries(SFMLRunner
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)
