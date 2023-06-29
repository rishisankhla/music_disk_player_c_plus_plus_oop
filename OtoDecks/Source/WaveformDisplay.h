/*
  ==============================================================================

    WaveformDisplay.h
    Created: 14 Mar 2020 3:50:16pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WaveformDisplay    : public Component, 
                           public ChangeListener
{
public:

    //constructor
    WaveformDisplay( AudioFormatManager & 	formatManagerToUse,
                    AudioThumbnailCache & 	cacheToUse );
    ~WaveformDisplay();

    // Juce library inbuilt paint function, purpose is to paint our song wave
    void paint (Graphics&) override;

    // Juce library resize function, purpose it set the "set-bound" property for each GUI object
    void resized() override;

    // juce library function, purpose to repaint
    void changeListenerCallback (ChangeBroadcaster *source) override;

    // load function, which takes URL as an parameter and loads the track
    void loadURL(URL audioURL);

    /** set the relative position of the playhead*/
    void setPositionRelative(double pos);

private:

    //our objects
    AudioThumbnail audioThumb;
    bool fileLoaded; 
    double position;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay) //juce library Macro
};
