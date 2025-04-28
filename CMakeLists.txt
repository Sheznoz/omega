# 1. Minimum required version
cmake_minimum_required(VERSION 3.10)

# 2. Project name and version
project(OmegaGame VERSION 0.1)

find_package( Boost COMPONENTS system REQUIRED )
find_package( Threads )

# 3. Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wreturn-type -Wreorder)

# 4. Set default build type if not specified (Debug/Release)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# 5. Add source and header files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS include/)

# 6. Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 7. Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(OmegaGame LINK_PUBLIC ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
