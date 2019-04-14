execute_process( COMMAND git submodule update --init --recursive )
set_directory_properties( PROPERTIES CLEAN_NO_CUSTOM 1) #do not delete the result of custom comands with "make clean"


## SDL2
set( SDL_STATIC OFF CACHE BOOL "Build the static SDL library" )
set( SDL_SHARED ON CACHE BOOL "Build the shared SDL library" )
add_subdirectory(sdl2)

## GLEW
set( glew-cmake_BUILD_SHARED ON CACHE BOOL "Build the shared glew library" )
set( glew-cmake_BUILD_STATIC OFF CACHE BOOL "Build the static glew library" )
set( glew-cmake_BUILD_SINGLE_CONTEXT ON CACHE BOOL "Build the single context glew library" )
set( glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "Build the multi context glew library" )
add_subdirectory( glew )

## imgui

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/imgui/)
add_library (imgui STATIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp)
