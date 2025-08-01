/*
  ==============================================================================

    SynthAudioSource.cpp
    Created: 29 Jul 2025 5:28:36pm
    Author:  Roman

  ==============================================================================
*/

#include "SynthAudioSource.h"

SynthAudioSource::SynthAudioSource(juce::MidiKeyboardState& keyState)
    : keyboardState(keyState)
{
    for (auto i = 0; i < 4; ++i)
        synth.addVoice(new SineWaveVoice());
    synth.addSound(new SineWaveSound());
}

void SynthAudioSource::setLevel(double level)
{
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        SineWaveVoice* voice = (SineWaveVoice*)synth.getVoice(i);
        voice->setLevel(level);
    }
}

void SynthAudioSource::setAttackIncrease(double attackIncrease)
{
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        SineWaveVoice* voice = (SineWaveVoice*)synth.getVoice(i);
        voice->setAttackIncrease(attackIncrease);
    }
}

void SynthAudioSource::setTailOffReduction(double tailOffReduction)
{
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        SineWaveVoice* voice = (SineWaveVoice*)synth.getVoice(i);
        voice->setTailOffReduction(tailOffReduction);
    }
}

void SynthAudioSource::setDecayReduction(double decayReduction)
{
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        SineWaveVoice* voice = (SineWaveVoice*)synth.getVoice(i);
        voice->setDecayReduction(decayReduction);
    }
}

void SynthAudioSource::toggleLevel(bool levelEnabled)
{
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        SineWaveVoice* voice = (SineWaveVoice*)synth.getVoice(i);
        voice->toggleLevel(levelEnabled);
    }
}

void SynthAudioSource::toggleAttack(bool attackEnabled)
{
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        SineWaveVoice* voice = (SineWaveVoice*)synth.getVoice(i);
        voice->toggleAttack(attackEnabled);
    }
}

void SynthAudioSource::toggleTailOff(bool tailOffEnabled)
{
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        SineWaveVoice* voice = (SineWaveVoice*)synth.getVoice(i);
        voice->toggleTailOff(tailOffEnabled);
    }
}

void SynthAudioSource::toggleDecay(bool decayEnabled)
{
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        SineWaveVoice* voice = (SineWaveVoice*)synth.getVoice(i);
        voice->toggleDecay(decayEnabled);
    }
}

void SynthAudioSource::setUsingSineWaveSound()
{
    synth.clearSounds();
}

void SynthAudioSource::prepareToPlay(int, double sampleRate)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void SynthAudioSource::releaseResources() {}

void SynthAudioSource::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();

    juce::MidiBuffer incomingMidi;
    keyboardState.processNextMidiBuffer(incomingMidi, bufferToFill.startSample,
        bufferToFill.numSamples, true);
    synth.renderNextBlock(*bufferToFill.buffer, incomingMidi,
        bufferToFill.startSample, bufferToFill.numSamples);
}
