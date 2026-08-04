cmake_minimum_required(VERSION 3.21)
project(HelloWorldApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

# --- APPLE AGL FRAMEWORK FIX ---
# Modern macOS SDKs removed AGL.framework.
# Redirect AGL requests directly to OpenGL.framework BEFORE Qt6 loads FindOpenGL.
if(APPLE)
    set(OPENGL_agl_LIBRARY "-framework OpenGL" CACHE STRING "Bypass missing AGL framework" FORCE)
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
install(TARGETS HelloWorldApp
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Generates deployment script to copy Qt dependencies
qt_generate_deploy_app_script(
    TARGET HelloWorldApp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

# --- CPACK PACKAGING ---
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
