cmake_minimum_required( VERSION 3.5 )

project(GUI_APP VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_library( nlohmann_json nlohmann_json )
add_executable( GUI )
file(COPY res DESTINATION ${CMAKE_BINARY_DIR})
file( GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
target_sources(GUI PRIVATE ${SRC_FILES})
target_include_directories(GUI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(GUI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/json/include)
target_link_libraries(GUI SDL3::SDL3
                          SDL3_image::SDL3_image
                          SDL3_mixer::SDL3_mixer
                          SDL3_ttf::SDL3_ttf
                          nlohmann_json)
