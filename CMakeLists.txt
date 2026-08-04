cmake_minimum_required(VERSION 3.21)
project(HelloWorldApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Standard install paths
include(GNUInstallDirs)

# --- APPLE AGL FRAMEWORK FIX ---
# Bypasses the missing AGL framework error on modern macOS SDKs
if(APPLE)
    find_package(OpenGL REQUIRED)
    set(OPENGL_agl_LIBRARY ${OPENGL_gl_LIBRARY} CACHE FILEPATH "Bypass AGL" FORCE)
endif()
# -------------------------------

# Find Qt6 and set up standard tools (moc, uic, rcc)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

# Define executable
qt_add_executable(HelloWorldApp main.cpp)

# Link Qt libraries
target_link_libraries(HelloWorldApp PRIVATE Qt6::Widgets)

# --- DEPLOYMENT & INSTALLATION ---
# Define where the executable goes when installed
install(TARGETS HelloWorldApp
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Generates the deployment script to copy Qt dependencies next to the executable
qt_generate_deploy_app_script(
    TARGET HelloWorldApp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

# --- CPACK PACKAGING ---
# Automatically generates .zip or .tar.gz archives containing the deployed app
set(CPACK_PACKAGE_NAME "HelloWorldApp")
set(CPACK_PACKAGE_VENDOR "Developer")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple Qt6 Hello World Application")

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
elseif(APPLE)
    set(CPACK_GENERATOR "ZIP")
else()
    set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)
