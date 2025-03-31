cmake_minimum_required(VERSION 3.15)
project(AppPluginBundle123 VERSION 1.0.0 LANGUAGES CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set iOS-specific deployment target
set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0" CACHE STRING "Minimum iOS deployment version")

# Add FetchContent module
include(FetchContent)

# Fetch Tracktion Engine (which includes JUCE)
FetchContent_Declare(
    tracktion_engine
    GIT_REPOSITORY https://github.com/Tracktion/tracktion_engine.git
    GIT_TAG        origin/master  # Consider using a specific tag for stability
)
FetchContent_MakeAvailable(tracktion_engine)

# Point to Tracktion Engine's bundled JUCE
set(JUCE_DIR "${tracktion_engine_SOURCE_DIR}/modules/JUCE")

# Define the main app target
juce_add_gui_app(AppPluginBundle123
    BUNDLE_ID                   com.example.apppluginbundle123
    COMPANY_NAME                "YourCompany"
    DOCUMENT_EXTENSIONS         ""
    NEEDS_CURL                  FALSE
    NEEDS_WEB_BROWSER           FALSE
    MICROPHONE_PERMISSION_ENABLED TRUE
    ICON_BIG                    "AppIcon.png"
    HARDENED_RUNTIME_ENABLED    TRUE
    APP_GROUPS_ENABLED          FALSE
)

# Generate JUCE header
juce_generate_juce_header(AppPluginBundle123)

# Source files
target_sources(AppPluginBundle123 PRIVATE
    Source/Main.cpp
    Source/MainComponent.h
    Source/MainComponent.cpp
)

# Include directories
target_include_directories(AppPluginBundle123 PRIVATE
    ${tracktion_engine_SOURCE_DIR}/modules
    ${JUCE_DIR}/modules
)

# Link libraries
target_link_libraries(AppPluginBundle123 PRIVATE
    tracktion_engine
    juce::juce_audio_utils
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    "-framework CoreAudio"
    "-framework CoreMIDI"
    "-framework AudioToolbox"
    "-framework AVFoundation"
)

# Compile definitions for standalone app only
target_compile_definitions(AppPluginBundle123 PRIVATE
    JUCE_STANDALONE_APPLICATION=1
    JUCE_USE_CURL=0
    JUCE_WEB_BROWSER=0
)

# Add plugin submodule (ensure it has its own CMakeLists.txt)
add_subdirectory(plugins/bundlePlugABC)

# Embed AUv3 plugin
set_target_properties(AppPluginBundle123 PROPERTIES
    XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS "${CMAKE_CURRENT_SOURCE_DIR}/Source/AppPluginBundle123.entitlements"
    XCODE_EMBED_APP_EXTENSIONS  bundlePlugABC
    XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
)
