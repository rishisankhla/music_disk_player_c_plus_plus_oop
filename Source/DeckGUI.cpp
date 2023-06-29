/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, 
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
           ) : player(_player), 
               waveformDisplay(formatManagerToUse, cacheToUse)
{
    //adding the objects to our application
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    //setting the style to our objects
    otherLookAndFeel.setColour(juce::Slider::thumbColourId, juce::Colours::red);
    speedSlider.setLookAndFeel(&otherLookAndFeel);

    reverb_1.setSliderStyle(juce::Slider::Rotary);
    reverb_2.setSliderStyle(juce::Slider::Rotary);
    reverb_3.setSliderStyle(juce::Slider::Rotary);
    reverb_4.setSliderStyle(juce::Slider::Rotary);
    reverb_5.setSliderStyle(juce::Slider::Rotary);
    reverb_6.setSliderStyle(juce::Slider::Rotary);
    reverb_1.setLookAndFeel(&otherLookAndFeel);
    reverb_2.setLookAndFeel(&otherLookAndFeel);
    reverb_3.setLookAndFeel(&otherLookAndFeel);
    reverb_4.setLookAndFeel(&otherLookAndFeel);
    reverb_5.setLookAndFeel(&otherLookAndFeel);
    reverb_6.setLookAndFeel(&otherLookAndFeel);

    //adding the objects to our application
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(reverb_1);
    addAndMakeVisible(reverb_2);
    addAndMakeVisible(reverb_3);
    addAndMakeVisible(reverb_4);
    addAndMakeVisible(reverb_5);
    addAndMakeVisible(reverb_6);
    addAndMakeVisible(waveformDisplay);

    //adding listeners
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    reverb_1.addListener(this);
    reverb_2.addListener(this);
    reverb_3.addListener(this);
    reverb_4.addListener(this);
    reverb_5.addListener(this);
    reverb_6.addListener(this);

    //setting ranges
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 1.0);
    posSlider.setRange(0.0, 1.0);
    reverb_1.setRange(0.0, 1.0);
    reverb_2.setRange(0.0, 1.0);
    reverb_3.setRange(0.0, 1.0);
    reverb_4.setRange(0.0, 1.0);
    reverb_5.setRange(0.0, 1.0);
    reverb_6.setRange(0.0, 1.0);

    startTimer(500);

}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("DeckGUI", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

//function to set layout
void DeckGUI::resized()
{
    double rowH = getHeight() / 8; 
    double rowW = getWidth() / 3;
    waveformDisplay.setBounds(0, 0, rowW * 3, rowH * 2);
    
    volSlider.setBounds(0, rowH * 2, rowW * 2, rowH);
    speedSlider.setBounds(0, rowH * 3, rowW * 2, rowH);
    posSlider.setBounds(0, rowH * 4, rowW * 2, rowH);
    
    reverb_1.setBounds(rowW * 2, rowH * 2, rowW * 1, rowH);
    reverb_2.setBounds(rowW * 2, rowH * 3, rowW * 1, rowH);
    reverb_3.setBounds(rowW * 2, rowH * 4, rowW * 1, rowH);
    reverb_4.setBounds(rowW * 2, rowH * 5, rowW * 1, rowH);
    reverb_5.setBounds(rowW * 2, rowH * 6, rowW * 1, rowH);
    reverb_6.setBounds(rowW * 2, rowH * 7, rowW * 1, rowH);

    playButton.setBounds(0, rowH * 5, rowW * 2, rowH);
    stopButton.setBounds(0, rowH * 6, rowW * 2, rowH);
    loadButton.setBounds(0, rowH * 7, rowW * 2, rowH);

}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
     if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();

    }
    if (button == &loadButton)
    {
        auto fileChooserFlags = 
        FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            player->loadURL(URL{chooser.getResult()});
            // and now the waveformDisplay as well
            waveformDisplay.loadURL(URL{chooser.getResult()}); 
        });
    }
}

//adding functionality to sliders
void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue()); //setting gain
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue()); //setting speed
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue()); //setting position
    }
    if (slider == &reverb_1)
    {
        player->setting_wet(slider->getValue()); //setting reverb_parameter_1
    }
    if (slider == &reverb_2)
    {
        player->setting_width(slider->getValue()); //setting reverb_parameter_2
    }
    if (slider == &reverb_3)
    {
        player->setting_damp(slider->getValue()); //setting reverb_parameter_3
    }
    if (slider == &reverb_4)
    {
        player->setting_dry(slider->getValue()); //setting reverb_parameter_4
    }
    if (slider == &reverb_5)
    {
        player->setting_room(slider->getValue()); //setting reverb_parameter_5
    }
    if (slider == &reverb_6)
    {
        player->setting_freez(slider->getValue()); //setting reverb_parameter_6
    }
}

//testing the file drag
bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

//file drag and drop function
void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
  }
}

//function to load the track to the appropriate disk
void DeckGUI::loadthecurrentfile(juce::URL our_audio)
{
    player->loadURL(our_audio);
    waveformDisplay.loadURL(our_audio);
}

//setting position accordingly
void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}



 

