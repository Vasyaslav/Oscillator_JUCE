/*
  ==============================================================================

    SineWaveSound.h
    Created: 29 Jul 2025 1:59:34pm
    Author:  Roman

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct SineWaveSound: public juce::SynthesiserSound
{
    SineWaveSound();
    
    bool appliesToNote    (int) override;
    bool appliesToChannel (int) override;
};