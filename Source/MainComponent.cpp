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
	addAndMakeVisible(levelLabel);
	levelLabel.setText("Level", juce::dontSendNotification);

	addAndMakeVisible(attackSlider);
	attackSlider.setRange(0.00005, 0.00025);
	attackSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
	attackSlider.onValueChange = [this] { synthAudioSource.setAttackIncrease(attackSlider.getValue()); };
	addAndMakeVisible(attackLabel);
	attackLabel.setText("Attack", juce::dontSendNotification);

	addAndMakeVisible(tailOffSlider);
	tailOffSlider.setRange(0.999, 0.9999);
	tailOffSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 100, 20);
	tailOffSlider.onValueChange = [this] { synthAudioSource.setTailOffReduction(tailOffSlider.getValue()); };
	addAndMakeVisible(tailOffLabel);
	tailOffLabel.setText("Tail off", juce::dontSendNotification);
	

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
	
	levelLabel.setBounds(10, 220, 90, 20);
	levelSlider.setBounds(100, 220, getWidth() - 110, 20);

	attackLabel.setBounds(10, 250, 90, 20);
	attackSlider.setBounds(100, 250, getWidth() - 110, 20);

	tailOffLabel.setBounds(10, 280, 90, 20);
	tailOffSlider.setBounds(100, 280, getWidth() - 110, 20);
	
}

void MainComponent::timerCallback() 
{
	keyboardComponent.grabKeyboardFocus();
	stopTimer();
}
