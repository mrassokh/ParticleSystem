cmake_minimum_required (VERSION 3.13)

project (ParticleSystem)


#add_subdirectory(includes)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenCL -framework OpenGL")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(src)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib) # Setup linker libs
add_subdirectory(3rdParty)

set ( GLEW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/glew/include )
set ( GLEW_LIBRARIES libglew_shared )

set ( SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/sdl2/include )
set ( SDL2_LIBRARY SDL2 )

set ( GLM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/glm/ )
set ( CL_CXX_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/CL/ )

set ( IMGUI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/imgui/ )
set ( IMGUI_LIBRARY imgui )


find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)

if (!${OpenCL_FOUND})
message("OpenCL not found")
return()
endif()

message("OpenCL found!")

message("OPENCL LIB:")
message( ${OpenCL_LIBRARIES} )

message("OPENCL INCLUDE DIRS:")
message(${OpenCL_INCLUDE_DIRS})


set(PARTICLESYSTEM_SOURCES
  ${PARTICLESYSTEM_LOCAL_SOURCES}
  ${PARTICLESYSTEM_LOCAL_INCLUDES}
 )

set(PARTICLESYSTEM_INCLUDE_DIRS
  includes
)

set(LIB_INCLUDE_DIRS
  libs/inc
)

add_library(hello SHARED libs/testlib.cpp)

set(PARTICLESYSTEM_LIBS
  	${OPENGL_LIBRARY}
  	${SDL2_LIBRARY}
  	${GLEW_LIBRARIES}
  	${IMGUI_LIBRARY}
  	${OpenCL_LIBRARIES}
)

set(PARTICLESYSTEM_INCLUDES
	${PARTICLESYSTEM_INCLUDE_DIRS}
	${LIB_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
  	${IMGUI_INCLUDE_DIRS}
  	${OpenCL_INCLUDE_DIRS}
	${CL_CXX_INCLUDE_DIRS}
)

include_directories(${PARTICLESYSTEM_INCLUDES})

add_executable(particleSystem main.cpp ${PARTICLESYSTEM_SOURCES})
target_link_libraries(particleSystem hello ${PARTICLESYSTEM_LIBS})
