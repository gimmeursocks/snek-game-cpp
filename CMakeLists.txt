cmake_minimum_required(VERSION 3.12)

project(snek VERSION 1.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

set(SRCDIR src)
set(INCLUDEDIR ${SRCDIR}/include)

file(GLOB SOURCES "${SRCDIR}/*.cpp")

include_directories(${INCLUDEDIR})

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${SDL2_INCLUDE_DIRS}
    PUBLIC ${SDL2_TTF_INCLUDE_DIRS}
    PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS}
)

if(WIN32 AND MINGW)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE TRUE
            LINK_FLAGS "-mwindows"
        )
    endif()

    target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image mingw32)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/${SRCDIR}/assets/icon.png
     DESTINATION ${CMAKE_BINARY_DIR}/${SRCDIR}/assets)