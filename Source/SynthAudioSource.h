/*
  ==============================================================================

    SinthAudioSource.h
    Created: 29 Jul 2025 2:00:18pm
    Author:  Roman

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SineWaveVoice.h"
#include "SineWaveSound.h"

class SynthAudioSource: public juce::AudioSource
{
public:
    SynthAudioSource(juce::MidiKeyboardState& keyState);
    void setUsingSineWaveSound();
    void prepareToPlay(int /*samplesPerBlockExpected*/, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void setLevel(double level);
    void setAttackIncrease(double attackIncrease);
    void setTailOffReduction(double tailOffReduction);
private:
    juce::MidiKeyboardState& keyboardState;
    juce::Synthesiser synth;
};