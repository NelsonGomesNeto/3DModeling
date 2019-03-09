cmake_minimum_required(VERSION 3.13)
project(3DModeling)

file(GLOB 3DModeling_src
        "*.h"
        "*.cpp"
        )

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "C:/mingw64")

add_executable(3DModeling ${3DModeling_src})

include_directories(C:/mingw64/include)

target_link_libraries(3DModeling -lOpenGL32 -lfreeGLUT -lglu32)