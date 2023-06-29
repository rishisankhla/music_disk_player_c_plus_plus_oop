/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 13 Mar 2020 4:22:22pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class DJAudioPlayer : public AudioSource {
  public:

    //constructor
    DJAudioPlayer(AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void loadURL(URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);
    

    void start();
    void stop();

    /** get the relative position of the playhead */
    double getPositionRelative();

    //reverb parameter functions, which take float as an argument
    void setting_dry(float d_level);
    void setting_damp(float da_level);
    void setting_room(float r_level);
    void setting_wet(float w_level);
    void setting_width(float wi_level);
    void setting_freez(float fr_level);

    //function which returns the track length in seconds
    double return_current_length();

private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource; 
    ResamplingAudioSource resampleSource{&transportSource, false, 2};
    juce::ReverbAudioSource our_reverb{ &resampleSource, false};
    juce::Reverb::Parameters our_r_parameter;

};




