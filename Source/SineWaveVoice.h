/*
  ==============================================================================

    SineWaveVoice.h
    Created: 29 Jul 2025 1:59:44pm
    Author:  Roman

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct SineWaveVoice: public juce::SynthesiserVoice
{ 
    SineWaveVoice();

    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity,
        juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override;
    void stopNote(float /*velocity*/, bool allowTailOff) override;
    void pitchWheelMoved(int) override;
    void controllerMoved(int, int) override;
    void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;
    void setLevel(double level);
    void setAttackIncrease(double attackIncrease);
    void setTailOffReduction(double tailOffReduction);

private:
    double currentAngle = 0.0, angleDelta = 0.0, level = 0.05, attack = 0.0, tailOff = 0.0;
    double  attackIncrease = 0.00005, tailOffReduction = 0.9999;
};