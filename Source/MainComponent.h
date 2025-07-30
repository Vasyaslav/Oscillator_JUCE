#pragma once

#include <JuceHeader.h>
#include "SynthAudioSource.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent, private juce::Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    
    juce::Slider levelSlider;
    juce::Label  levelLabel;
    double currentLevel = 0.0, targetLevel = 0.0;

    juce::Slider attackSlider;
    juce::Label  attackLabel;

    juce::Slider tailOffSlider;
    juce::Label  tailOffLabel;
    
    juce::MidiKeyboardState keyboardState;
    SynthAudioSource synthAudioSource;
    juce::MidiKeyboardComponent keyboardComponent;
    void timerCallback() override;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
