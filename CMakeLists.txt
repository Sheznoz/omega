# 1. Minimum required version (3.15 is good, 3.19+ for CMP0167 without warning)
cmake_minimum_required(VERSION 3.15) # Changed to 3.15, as that's what you had.

# Policy for modern Boost discovery. This is essential for find_package(... CONFIG).
cmake_policy(SET CMP0167 NEW)

# 2. Project name and version
project(OmegaGame VERSION 0.1) # Specify language directly in project()

# 3. Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Use ON for boolean true
set(CMAKE_CXX_EXTENSIONS OFF)      # Prefer standard C++ over GNU extensions if not needed

# Add common compile options (for -Wreturn-type, etc.)
# target_compile_options is preferred over global add_compile_options for executables
# target_compile_options(${PROJECT_NAME} PRIVATE -Wreturn-type -Wreorder) # Apply to target

# --- Global compile options (if you really want them global for all targets) ---
add_compile_options(
    -Wreturn-type
    -Wreorder
    # Add any other global flags you need
)
# --- End global compile options ---

# 4. Set default build type if not specified (Debug/Release)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# 5. Find Dependencies
# Use find_package with CONFIG for modern Boost discovery.
# 'system' is a common dependency for many Boost parts.
# You only list 'system'. If 'asio' is truly header-only for your use case and
# doesn't require explicit linking, this is fine. If it *does* need linking,
# you'd add 'asio' here: find_package(Boost COMPONENTS system asio REQUIRED CONFIG)
find_package(Boost COMPONENTS system REQUIRED CONFIG)
find_package(Threads REQUIRED) # Add REQUIRED for clarity if it's essential

# 6. Define Source Files (Prefer explicit listing or more controlled methods)
# REMOVE HEADERS from this list for add_executable
# Explicitly list source files, or use a list variable.
set(OMEGA_GAME_SOURCES
    src/main.cpp
    # Add other .cpp files here: src/another_file.cpp, etc.
)

# 7. Create executable
# DO NOT add header files directly to add_executable
add_executable(${PROJECT_NAME} ${OMEGA_GAME_SOURCES})

# 8. Include directories and Link Libraries
# Use target-specific commands where possible.

# Your project's own include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# --- Boost & Threads Linkage ---
if(Boost_FOUND)
    # Link to Boost's imported targets for headers and libraries
    target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system) # Link to Boost::system
    # If Boost.Asio also requires linking (not just header-only), uncomment this:
    # target_link_libraries(${PROJECT_NAME} PRIVATE Boost::asio)
else()
    message(FATAL_ERROR "Boost not found. Please check your installation.")
endif()

if(THREADS_FOUND)
    # Link to Threads library
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
else()
    message(WARNING "Threads library not found. Some functionality might be missing.")
endif()

# --- Explicitly Add Homebrew Boost Include Path for clangd ---
# This is mainly for clangd, as the compiler might find it anyway,
# but it ensures the -I flag is in compile_commands.json.
# This should happen *before* target_link_libraries for Boost if you rely on it
# for *some* headers not brought in by target properties.
if (APPLE)
    execute_process(
        COMMAND brew --prefix boost
        OUTPUT_VARIABLE BOOST_HOMEBREW_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(EXISTS "${BOOST_HOMEBREW_PREFIX}/include")
        message(STATUS "Adding Boost Homebrew include path: ${BOOST_HOMEBREW_PREFIX}/include")
        # Use target_include_directories for target-specific includes
        target_include_directories(${PROJECT_NAME} PRIVATE "${BOOST_HOMEBREW_PREFIX}/include")
    else()
        message(WARNING "Could not find Boost Homebrew include path at ${BOOST_HOMEBREW_PREFIX}/include. clangd might complain.")
    endif()
endif()
