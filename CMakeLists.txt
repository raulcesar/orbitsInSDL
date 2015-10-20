cmake_minimum_required(VERSION 3.1)
project(OrbitsInSDL)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)


# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()



# if(UNIX)
#     SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
# endif()
#set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)



# FIND_PACKAGE ( Threads REQUIRED )

include_directories(
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	# ${GTK3_INCLUDE_DIRS}
	# ${GTKMM_INCLUDE_DIRS}
#	${Boost_INCLUDE_DIRS}
	# ${CMAKE_CURRENT_SOURCE_DIR}/libs
	)

MESSAGE( STATUS "Hey yall!" )
MESSAGE( STATUS ${SDL2_INCLUDE_DIR} )
MESSAGE( STATUS ${CMAKE_BINARY_DIR} )


# Look in the src subdirectory to find its CMakeLists.txt so we can build the executable
# add_subdirectory(src)


file(GLOB SOURCE_FILES src/*.cpp)
file(GLOB HEADER_FILES src/*.hpp)

file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})

# file(GLOB HEADER_FILES src/*.hpp)
# file(GLOB GLADE_FILES *.glade)

# set(SOURCE_FILES 
# 	main.cpp
# 	renderer.h
# 	gtkRenderer.cpp
# 	gtkRenderer.h
# 	rayTracer.cpp
# 	rayTracer.h
# 	world.cpp
# 	world.h
# 	geometricObject.cpp
# 	geometricObject.h
# 	main.glade
# 	)

# file(COPY main.glade DESTINATION yourDestination)
# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/main.glade ${CMAKE_CURRENT_BINARY_DIR}/main.glade COPYONLY)

# find_package(X11 REQUIRED)


add_executable(orbiterSim ${HEADER_FILES} ${SOURCE_FILES} )
# include_directories(${X11_INCLUDE_DIR})

# Link the target to the GTK+ libraries
target_link_libraries(orbiterSim 
	${SDL2_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	# ${GTK3_LIBRARIES}
	# ${GTKMM_LIBRARIES}
	# ${CMAKE_THREAD_LIBS_INIT}
#	${Boost_FILESYSTEM_LIBRARY}
#  	${Boost_SYSTEM_LIBRARY}
#  	${Boost_REGEX_LIBRARY}
	)
# target_link_libraries (xlibHello
# 	${X11_LIBRARIES}
# )

install(TARGETS orbiterSim RUNTIME DESTINATION ${BIN_DIR})