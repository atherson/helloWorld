cmake_minimum_required(VERSION 3.16)
project(HelloWorldApp VERSION 1.0 LANGUAGES CXX)

# Fix for macOS Xcode 15+ where legacy AGL.framework was removed
if(APPLE)
    set(OPENGL_agl_LIBRARY "" CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
