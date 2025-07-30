/*
  ==============================================================================

    SineWaveVoice.cpp
    Created: 29 Jul 2025 5:28:47pm
    Author:  Roman

  ==============================================================================
*/

#include "SineWaveVoice.h"
#include "SineWaveSound.h"

SineWaveVoice::SineWaveVoice() {}

bool SineWaveVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<SineWaveSound*> (sound) != nullptr;
}

void SineWaveVoice::startNote(int midiNoteNumber, float velocity,
    juce::SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
    currentAngle = 0.0;
    level *= velocity;
    tailOff = 0.0;
    attack = 0.0;

    auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();

    angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
}

void SineWaveVoice::stopNote(float /*velocity*/, bool allowtailOff)
{
    if (allowtailOff)
    {
        if (tailOff == 0.0)
            tailOff = 1.0;
    }
    else
    {
        clearCurrentNote();
        angleDelta = 0.0;
    }
}

void SineWaveVoice::pitchWheelMoved(int) {}

void SineWaveVoice::controllerMoved(int, int) {}

void SineWaveVoice::renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    if (angleDelta != 0.0)
    {
        while (--numSamples >= 0)
        {
            double k = 1.0;
            if (attack < 1.0)
            {
                attack += attackIncrease;
                k *= attack;
            }
            if (tailOff > 0.0)
            {
                tailOff *= tailOffReduction;

                k *= tailOff;
                if (tailOff <= 0.005)
                {
                    clearCurrentNote();

                    angleDelta = 0.0;
                    break;
                }
            }
            auto currentSample = (float)(std::sin(currentAngle) * level * k);

            for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample(i, startSample, currentSample);

            currentAngle += angleDelta;
            ++startSample;
        }
    }
}

void SineWaveVoice::setLevel(double level)
{
    this->level = level;
}

void SineWaveVoice::setAttackIncrease(double attackIncrease)
{
    this->attackIncrease = attackIncrease;
}

void SineWaveVoice::setTailOffReduction(double tailOffReduction)
{
    this->tailOffReduction = tailOffReduction;
}
