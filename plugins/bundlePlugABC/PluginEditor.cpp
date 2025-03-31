#include "PluginEditor.h"

BundlePlugABCEditor::BundlePlugABCEditor(BundlePlugABCProcessor& p)
    : AudioProcessorEditor(&p), processor(p) {
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(gainLabel);

    gainSlider.setSliderStyle(juce::Slider::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(gainSlider);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.getParameterTree(), "gain", gainSlider);

    setSize(200, 300);
}

BundlePlugABCEditor::~BundlePlugABCEditor() {}

void BundlePlugABCEditor::paint(juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void BundlePlugABCEditor::resized() {
    auto area = getLocalBounds().reduced(10);
    gainLabel.setBounds(area.removeFromTop(20));
    gainSlider.setBounds(area);
}
