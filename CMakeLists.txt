cmake_minimum_required(VERSION 3.16)
project(HelloWorldApp VERSION 1.0 LANGUAGES CXX)

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

# 1. Instruct CMake where to place the executable on install
install(TARGETS HelloWorldApp
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 2. Automatically generate a deployment script to grab Qt DLLs/libraries
qt_generate_deploy_app_script(
    TARGET HelloWorldApp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
