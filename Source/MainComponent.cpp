#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() 
	: synthAudioSource(keyboardState),
	  keyboardComponent(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
	
	addAndMakeVisible(levelSlider);
	levelSlider.setRange(0.0, 0.15);
	levelSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
	levelSlider.onValueChange = [this] { synthAudioSource.setLevel(levelSlider.getValue()); };
	levelSlider.setValue(0.05);
	addAndMakeVisible(levelLabel);
	levelLabel.setText("Level", juce::dontSendNotification);
	addAndMakeVisible(levelToggle);
	levelToggle.setToggleState(true, juce::dontSendNotification);
	levelToggle.onClick = [this] { 
		synthAudioSource.toggleLevel(levelToggle.getToggleState());
		synthAudioSource.setLevel(levelSlider.getValue()); 
		};

	addAndMakeVisible(attackSlider);
	attackSlider.setRange(0.00001, 0.00025);
	attackSlider.setSkewFactorFromMidPoint(0.00005);
	attackSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
	attackSlider.onValueChange = [this] { synthAudioSource.setAttackIncrease(attackSlider.getMaximum() - attackSlider.getValue() + attackSlider.getMinimum()); };
	attackSlider.setValue(0.00005);
	addAndMakeVisible(attackLabel);
	attackLabel.setText("Attack", juce::dontSendNotification);
	addAndMakeVisible(attackToggle);
	attackToggle.setToggleState(true, juce::dontSendNotification);
	attackToggle.onClick = [this] { synthAudioSource.toggleAttack(attackToggle.getToggleState()); };

	addAndMakeVisible(decaySlider);
	decaySlider.setRange(0.00001, 0.00025);
	decaySlider.setSkewFactorFromMidPoint(0.00005);
	decaySlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
	decaySlider.onValueChange = [this] { synthAudioSource.setDecayReduction(decaySlider.getMaximum() - decaySlider.getValue() + decaySlider.getMinimum()); };
	decaySlider.setValue(0.00005);
	addAndMakeVisible(decayLabel);
	decayLabel.setText("Decay", juce::dontSendNotification);
	addAndMakeVisible(decayToggle);
	decayToggle.setToggleState(true, juce::dontSendNotification);
	decayToggle.onClick = [this] { synthAudioSource.toggleDecay(decayToggle.getToggleState()); };

	addAndMakeVisible(tailOffSlider);
	tailOffSlider.setRange(0.00001, 0.00025);
	tailOffSlider.setSkewFactorFromMidPoint(0.00005);
	tailOffSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
	tailOffSlider.onValueChange = [this] { synthAudioSource.setTailOffReduction(tailOffSlider.getMaximum() - tailOffSlider.getValue() + tailOffSlider.getMinimum()); };
	tailOffSlider.setValue(0.00005);
	addAndMakeVisible(tailOffLabel);
	tailOffLabel.setText("Tail off", juce::dontSendNotification);
	addAndMakeVisible(tailOffToggle);
	tailOffToggle.setToggleState(true, juce::dontSendNotification);
	tailOffToggle.onClick = [this] { synthAudioSource.toggleTailOff(tailOffToggle.getToggleState()); };
	

	addAndMakeVisible(keyboardComponent);
	// Make sure you set the size of the component after you add any child components.
	setSize(800, 340);

	// Some platforms require permissions to open input channels so request that here
	setAudioChannels(0, 2);

	startTimer(400);
}

MainComponent::~MainComponent()
{
	// This shuts down the audio device and clears the audio source.
	shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	synthAudioSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	synthAudioSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
	synthAudioSource.releaseResources();
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	// You can add your drawing code here!
}

void MainComponent::resized()
{
	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
	keyboardComponent.setBounds(10, 10, getWidth() - 20, 200);
	
	levelLabel.setBounds(10, 220, 60, 20);
	levelToggle.setBounds(70, 220, 25, 20);
	levelSlider.setBounds(100, 220, getWidth() - 110, 20);

	attackLabel.setBounds(10, 250, 60, 20);
	attackToggle.setBounds(70, 250, 25, 20);
	attackSlider.setBounds(100, 250, getWidth() - 110, 20);
	
	decayLabel.setBounds(10, 280, 60, 20);
	decayToggle.setBounds(70, 280, 25, 20);
	decaySlider.setBounds(100, 280, getWidth() - 110, 20);

	tailOffLabel.setBounds(10, 310, 60, 20);
	tailOffToggle.setBounds(70, 310, 25, 20);
	tailOffSlider.setBounds(100, 310, getWidth() - 110, 20);
}

void MainComponent::timerCallback() 
{
	keyboardComponent.grabKeyboardFocus();
	stopTimer();
}
