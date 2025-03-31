#include "MainComponent.h"

MainComponent::MainComponent() {
    titleLabel.setText("AppPluginBundle123", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(24.0f));
    titleLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(titleLabel);
    setSize(400, 300);
}

MainComponent::~MainComponent() {}

void MainComponent::paint(juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized() {
    titleLabel.setBounds(getLocalBounds().reduced(10));
}
