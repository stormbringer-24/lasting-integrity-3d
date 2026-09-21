cmake_minimum_required(VERSION 3.10)
project(Lasting_Integrity LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Lasting_Integrity
    src/main.cpp
)

target_include_directories(Lasting_Integrity
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(OpenGL REQUIRED)

set(GLFW_TARGET "")
find_package(glfw3 CONFIG QUIET)
if(TARGET glfw)
    set(GLFW_TARGET glfw)
elseif(TARGET glfw3)
    set(GLFW_TARGET glfw3)
else()
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(GLFW QUIET glfw3)
    endif()

    if(GLFW_FOUND)
        target_include_directories(Lasting_Integrity PRIVATE ${GLFW_INCLUDE_DIRS})
        target_link_libraries(Lasting_Integrity PRIVATE ${GLFW_LIBRARIES})
    else()
        find_library(GLFW_LIBRARY NAMES glfw glfw3 REQUIRED)
        target_link_libraries(Lasting_Integrity PRIVATE ${GLFW_LIBRARY})
    endif()
endif()

if(GLFW_TARGET)
    target_link_libraries(Lasting_Integrity PRIVATE ${GLFW_TARGET})
endif()

set(GLEW_TARGET "")
find_package(GLEW QUIET)
if(TARGET GLEW::GLEW)
    set(GLEW_TARGET GLEW::GLEW)
elseif(TARGET GLEW::glew)
    set(GLEW_TARGET GLEW::glew)
else()
    find_library(GLEW_LIBRARY NAMES GLEW glew32 glew REQUIRED)
    target_link_libraries(Lasting_Integrity PRIVATE ${GLEW_LIBRARY})
endif()

if(GLEW_TARGET)
    target_link_libraries(Lasting_Integrity PRIVATE ${GLEW_TARGET})
endif()

if(TARGET OpenGL::GL)
    target_link_libraries(Lasting_Integrity PRIVATE OpenGL::GL)
elseif(TARGET OpenGL::OpenGL)
    target_link_libraries(Lasting_Integrity PRIVATE OpenGL::OpenGL)
else()
    target_link_libraries(Lasting_Integrity PRIVATE ${OPENGL_LIBRARIES})
endif()

if(APPLE)
    target_link_libraries(Lasting_Integrity PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()
