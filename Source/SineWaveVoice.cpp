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
	attack = 0.0;
	decay = 0.0;
	tailOff = 0.0;

	auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	auto cyclesPerSample = cyclesPerSecond / getSampleRate();

	angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
}

void SineWaveVoice::stopNote(float /*velocity*/, bool allowtailOff)
{
	decay = decayEnabled ? 1.0 : 0.0; // If user don't have decay enabled then we should start tail off immediatly
	if (attackEnabled)
	{
		tailOff = attack; // Tail off and decay should start from attack volume, not 1.0 (full volume of current level)
		decayVolume = attack; // decay itself represents duration 
	}
	else
	{
		tailOff = 1.0;
		decayVolume = 1.0;
	}
	
	attack = 1.0;     // Then attack is set to 1.0 to ignore its "if" statement in renderNextBlock

	/* Some MIDI devices can decide if they should have tail off on its own
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
	*/
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
			// ------ Changing level of sound based on attack, decay and tail off states and values
			if (!attackEnabled && !decayEnabled && !tailOffEnabled && !isKeyDown()) // If we have everything disabled we play on immediate full volume until note release
			{
				clearCurrentNote(); 

				angleDelta = 0.0;
				break;
			}
			if (attackEnabled && attack != 1.0) // If attack is enabled we increase it until it has full volume
			{
				attack += attackIncrease;
				if (attack > 1.0 - attackIncrease * 2)
				{
					attack = 1.0;
					
				}
				k *= attack;
			}
			if (decay > 0.0) // Decay initial value is set in stopNote based on its state (enabled/disabled) so we don't check state here
			{
				decay -= decayReduction;
				k *= decayVolume;
				if (decay < decayReduction * 2 && !tailOffEnabled) // If we don't have tail off, stop playing when decay is very low
				{
					clearCurrentNote();

					angleDelta = 0.0;
					break;
				}
			}
			if (tailOffEnabled && tailOff > 0.0 && decay <= 0.0) // Play tail off only when decay ended
			{
				tailOff -= tailOffReduction;

				k *= tailOff;
				if (tailOff <= tailOffReduction * 2)
				{
					clearCurrentNote(); // If we have tail off, stop playing when tail off is very low

					angleDelta = 0.0;
					break;
				}
			}
			if (!levelEnabled) // if level enabled (we set it to current slider value when user toggle it back on)
			{
				level = 0.0;
			}
			
			auto currentSample = (float)(std::sin(currentAngle) * level * k);

			for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
				outputBuffer.addSample(i, startSample, currentSample);

			currentAngle += angleDelta;
			++startSample;

			if (attack == 1.0 && !decayEnabled && !tailOffEnabled)  // If we don't have tail off or decay stop playing when attack ended
			{
				// Placed outside attack "if" cuz attack is set to 1.0 in stopNote, so we won't get into attack "if", if note releases before attack reaches 1.0
				clearCurrentNote();
				angleDelta = 0.0;
				break;
			}
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

void SineWaveVoice::setDecayReduction(double decayReduction)
{
	this->decayReduction = decayReduction;
}

void SineWaveVoice::toggleLevel(bool levelEnabled)
{
	this->levelEnabled = levelEnabled;
}

void SineWaveVoice::toggleAttack(bool attackEnabled)
{
	this->attackEnabled = attackEnabled;
}

void SineWaveVoice::toggleTailOff(bool tailOffEnabled)
{
	this->tailOffEnabled = tailOffEnabled;
}

void SineWaveVoice::toggleDecay(bool decayEnabled)
{
	this->decayEnabled = decayEnabled;
}