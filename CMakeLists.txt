cmake_minimum_required (VERSION 3.13)

project (ParticleSystem)


#add_subdirectory(includes)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)
add_subdirectory(src)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib) # Setup linker libs
add_subdirectory(3rdParty)

set ( ASSIMP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/assimp/include )
set ( ASSIMP_LIBRARY assimp )

set(PARTICLESYSTEM_SOURCES
  ${PARTICLESYSTEM_LOCAL_SOURCES}
 )

set(PARTICLESYSTEM_INCLUDE_DIRS
  includes
)

set(LIB_INCLUDE_DIRS
  libs/inc
)

set(PARTICLESYSTEM_INCLUDES
	${PARTICLESYSTEM_INCLUDE_DIRS}
	${LIB_INCLUDE_DIRS}
	${ASSIMP_INCLUDE_DIR}
)

include_directories(${PARTICLESYSTEM_INCLUDES})

add_library(hello SHARED libs/testlib.cpp)

add_executable(particleSystem main.cpp ${PARTICLESYSTEM_SOURCES})
target_link_libraries(particleSystem hello ${ASSIMP_LIBRARY})
