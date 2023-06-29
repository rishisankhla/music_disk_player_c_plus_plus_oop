/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/

//crerated a new class, by studing juce documentation website.
//reference:  /** https://docs.juce.com/master/tutorial_look_and_feel_customisation.html */
class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:

    //setting up the constructor function
    OtherLookAndFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colours::red);
    }

    //public overriding drawRotarySlider to draw our rotating sliders
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
    {
        auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
        auto centreX = (float)x + (float)width * 0.5f;
        auto centreY = (float)y + (float)height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // fill
        g.setColour(juce::Colours::orange);
        g.fillEllipse(rx, ry, rw, rw);

        // outline
        g.setColour(juce::Colours::red);
        g.drawEllipse(rx, ry, rw, rw, 1.0f);

        juce::Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 2.0f;
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

        // pointer
        g.setColour(juce::Colours::yellow);
        g.fillPath(p);
    }
};

//our main DeckGUI class
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget, 
                   public Timer
{
public:

    //constructor
    DeckGUI(DJAudioPlayer* player, 
           AudioFormatManager & 	formatManagerToUse,
           AudioThumbnailCache & 	cacheToUse );
    ~DeckGUI();

    // Juce library inbuilt paint function, purpose is to paint our each deck GUI
    void paint (Graphics&) override;

    // Juce library resize function, purpose it set the "set-bound" property for each GUI object
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    //file drag and drop functions
    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override; 
    void timerCallback() override; 
    void loadthecurrentfile(juce::URL our_audio);

private:

    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    Slider volSlider; 
    Slider speedSlider;
    Slider reverb_1;
    Slider reverb_2;
    Slider reverb_3;
    Slider reverb_4;
    Slider reverb_5;
    Slider reverb_6;
    Slider posSlider;
    FileChooser fChooser{"Select a file..."};
    OtherLookAndFeel otherLookAndFeel;
    WaveformDisplay waveformDisplay;
    DJAudioPlayer* player;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI) //juce library Macro
};
