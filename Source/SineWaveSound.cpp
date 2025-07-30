/*
  ==============================================================================

    SineWaveSound.cpp
    Created: 29 Jul 2025 5:28:56pm
    Author:  Roman

  ==============================================================================
*/

#include "SineWaveSound.h"


SineWaveSound::SineWaveSound() {}

bool SineWaveSound::appliesToNote(int) { return true; }

bool SineWaveSound::appliesToChannel(int) { return true; }