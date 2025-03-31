#include "PluginProcessor.h"
#include "PluginEditor.h"

BundlePlugABCProcessor::BundlePlugABCProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo())
                                     .withOutput("Output", juce::AudioChannelSet::stereo())) {
    gainParam = new juce::AudioParameterFloat("gain", "Gain", 0.0f, 1.0f, 0.5f);
    addParameter(gainParam);
}

BundlePlugABCProcessor::~BundlePlugABCProcessor() {}

void BundlePlugABCProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {}

void BundlePlugABCProcessor::releaseResources() {}

void BundlePlugABCProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    float gain = *gainParam;
    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        auto* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            channelData[sample] *= gain;
        }
    }
}

juce::AudioProcessorEditor* BundlePlugABCProcessor::createEditor() {
    return new BundlePlugABCEditor(*this);
}

void BundlePlugABCProcessor::getStateInformation(juce::MemoryBlock& destData) {
    juce::ValueTree state("bundlePlugABC");
    state.setProperty("gain", gainParam->get(), nullptr);
    juce::MemoryOutputStream(destData, true).writeString(state.toXmlString());
}


void BundlePlugABCProcessor::setStateInformation(const void* data, int sizeInBytes) {
    auto xml = juce::XmlDocument::parse(juce::MemoryInputStream(data, static_cast<size_t>(sizeInBytes), false).readEntireStreamAsString());
    if (xml) {
        auto state = juce::ValueTree::fromXml(*xml);
        if (state.hasProperty("gain"))
            *gainParam = state.getProperty("gain");
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new BundlePlugABCProcessor();
}
