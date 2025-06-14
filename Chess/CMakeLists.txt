cmake_minimum_required(VERSION 3.15)
project(Chess)

# ---- C++ standard ----
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else()
    set(CMAKE_CXX_STANDARD 20)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Warning flags for MSVC ----
if (MSVC)
    add_compile_options(/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif()

# ---- Gather sources ----
file(GLOB_RECURSE CHESS_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# ---- Define the executable ----
add_executable(Chess
    ${CHESS_SOURCES}
)

# ---- Include directories ----
# Must come *after* add_executable so the target exists
target_include_directories(Chess
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

# (Optional) link libraries here
# target_link_libraries(Chess PRIVATE some_library)
