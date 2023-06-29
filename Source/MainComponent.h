/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    //constructor
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================

    // Juce library inbuilt paint function, purpose is to paint our whole GUI
    void paint (Graphics& g) override;

    // Juce library resize function, purpose it set the "set-bound" property for each GUI object
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
     
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100}; 

    DJAudioPlayer player_extra_DJAudioPlayer{formatManager};

    DJAudioPlayer player1{formatManager};
    DeckGUI deckGUI1{&player1, formatManager, thumbCache}; 

    DJAudioPlayer player2{formatManager};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache}; 

    MixerAudioSource mixerSource; 
    
    PlaylistComponent PlaylistComponent{&deckGUI1,&deckGUI2, &player_extra_DJAudioPlayer };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent) //juce library Macro
};
