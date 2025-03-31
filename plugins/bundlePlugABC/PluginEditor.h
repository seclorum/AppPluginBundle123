#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class BundlePlugABCEditor : public juce::AudioProcessorEditor {
public:
    BundlePlugABCEditor(BundlePlugABCProcessor&);
    ~BundlePlugABCEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    BundlePlugABCProcessor& processor;
    juce::Slider gainSlider;
    juce::Label gainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BundlePlugABCEditor)
};
