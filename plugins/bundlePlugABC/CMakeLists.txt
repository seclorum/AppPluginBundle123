cmake_minimum_required(VERSION 3.15)
project(bundlePlugABC VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the AUv3 plugin target
juce_add_plugin(bundlePlugABC
    BUNDLE_ID                   com.example.bundlePlugABC
    COMPANY_NAME                "YourCompany"
    FORMATS                     AUv3
    PLUGIN_NAME                 "bundlePlugABC"
    DESCRIPTION                 "A simple gain control plugin"
    IS_SYNTH                    FALSE
    NEEDS_MIDI_INPUT            FALSE
    NEEDS_MIDI_OUTPUT           FALSE
    IS_MIDI_EFFECT              FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD     FALSE
)

# Generate JUCE header
juce_generate_juce_header(bundlePlugABC)

# Source files for the plugin
target_sources(bundlePlugABC PRIVATE
    PluginProcessor.cpp
    PluginProcessor.h
    PluginEditor.cpp
    PluginEditor.h
)

target_include_directories(bundlePlugABC PRIVATE
    ${JUCE_DIR}/modules
    ${tracktion_engine_SOURCE_DIR}/modules
)



# Link necessary frameworks and libraries
target_link_libraries(bundlePlugABC PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    tracktion_engine
    "-framework CoreAudio"
    "-framework AudioToolbox"
    "-framework AVFoundation"
)

# Define compile definitions
#target_compile_definitions(bundlePlugABC PRIVATE
#    JUCE_STANDALONE_APPLICATION=0
#)

target_compile_definitions(bundlePlugABC PRIVATE
    JUCE_USE_CURL=0
    JUCE_WEB_BROWSER=0
    # Note: JUCE_STANDALONE_APPLICATION is not defined here, letting JUCE’s plugin defaults apply
)

# Set AUv3-specific properties
set_target_properties(bundlePlugABC PROPERTIES
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.example.bundlePlugABC"
    XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS "${CMAKE_CURRENT_SOURCE_DIR}/bundlePlugABC.entitlements"
)
