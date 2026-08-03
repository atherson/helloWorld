cmake_minimum_required(VERSION 3.16)
project(HelloWorldApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- APPLE AGL FRAMEWORK FIX ---
# Find standard OpenGL first, then trick CMake into using it instead of the missing AGL framework
if(APPLE)
    find_package(OpenGL REQUIRED)
    set(OPENGL_agl_LIBRARY ${OPENGL_gl_LIBRARY} CACHE FILEPATH "Bypass AGL" FORCE)
endif()
# -------------------------------

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

# Define your executable target
qt_add_executable(HelloWorldApp
    main.cpp
)

# Link the required libraries
target_link_libraries(HelloWorldApp PRIVATE
    Qt6::Widgets
)

# --- PORTABLE DEPLOYMENT CONFIGURATION ---

install(TARGETS HelloWorldApp
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET HelloWorldApp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
