/*
==============================================================================

DJAudioPlayer.cpp
Created: 13 Mar 2020 4:22:22pm
Author:  matthew

==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager) 
: formatManager(_formatManager)
{
    //initial reverbs
    our_r_parameter.dryLevel = 0.4f;
    our_r_parameter.roomSize = 0.5f;
    our_r_parameter.damping = 0.5f;
    our_r_parameter.wetLevel = 0.0f;
    our_r_parameter.width = 1.0f;
    our_r_parameter.freezeMode = 0.0f;
    
    our_reverb.setParameters(our_r_parameter);

}
DJAudioPlayer::~DJAudioPlayer()
{

}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) 
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    our_reverb.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void DJAudioPlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    //resampleSource.getNextAudioBlock(bufferToFill);
    our_reverb.getNextAudioBlock(bufferToFill);

}
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {       
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, 
true)); 
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);             
        readerSource.reset (newSource.release());          
    }
}
void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    }
   
}
void DJAudioPlayer::setSpeed(double ratio)
{
  if (ratio < 0 || ratio > 100.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}
void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
     if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}


void DJAudioPlayer::start()
{
    transportSource.start();
}
void DJAudioPlayer::stop()
{
  transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

void DJAudioPlayer::setting_dry(float d_level)
{
    if (d_level < 0 || d_level > 1.0)
    {
        DBG("please enter between 0 to 1");
    }
    else {
        our_r_parameter.dryLevel = d_level;
        our_reverb.setParameters(our_r_parameter);
    }
}

void DJAudioPlayer::setting_damp(float da_level)
{
    if (da_level < 0 || da_level > 1.0)
    {
        DBG("please enter between 0 to 1");
    }
    else {
        our_r_parameter.damping = da_level;
        our_reverb.setParameters(our_r_parameter);
    }
}

void DJAudioPlayer::setting_room(float r_level)
{
    if (r_level < 0 || r_level > 1.0)
    {
        DBG("please enter between 0 to 1");
    }
    else {
        DBG("room changed");
        our_r_parameter.roomSize = r_level;
        our_reverb.setParameters(our_r_parameter);
    }
}

void DJAudioPlayer::setting_wet(float w_level)
{
    if (w_level < 0 || w_level > 1.0)
    {
        DBG("please enter between 0 to 1");
    }
    else {
        our_r_parameter.wetLevel = w_level;
        our_reverb.setParameters(our_r_parameter);
    }
}

void DJAudioPlayer::setting_width(float wi_level)
{
    if (wi_level < 0 || wi_level > 1.0)
    {
        DBG("please enter between 0 to 1");
    }
    else {
        our_r_parameter.width = wi_level;
        our_reverb.setParameters(our_r_parameter);
    }
}

void DJAudioPlayer::setting_freez(float fr_level)
{
    if (fr_level < 0 || fr_level > 1.0)
    {
        DBG("please enter between 0 to 1");
    }
    else {
        our_r_parameter.freezeMode = fr_level;
        our_reverb.setParameters(our_r_parameter);
    }
}

double DJAudioPlayer::return_current_length()
{
    return transportSource.getLengthInSeconds();;
}
