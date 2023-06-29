/*
  ==============================================================================

    PlaylistComponent.h
    Created: 30 Aug 2022 2:31:45am
    Author:  rishi

  ==============================================================================
*/

#pragma once
#include <vector>
#include <JuceHeader.h>
#include <string>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include <fstream>
//==============================================================================
/*
*/
class PlaylistComponent    : public Component,
                             public TableListBoxModel,
                             public Button::Listener,
                             public juce::TextEditor::Listener
{
public:

    //constructor
    PlaylistComponent(DeckGUI* _deck_1, DeckGUI* _deck_2,DJAudioPlayer* _player_extra_DJAudioPlayer);
    ~PlaylistComponent();

    // Juce library inbuilt paint function, purpose is to paint our playlist table 
    void paint (Graphics&) override;

    // Juce library resize function, purpose it set the "set-bound" property for each GUI object
    void resized() override;

    //function to return the track vector(containing the title of each track) length
    int getNumRows() override;

    //juce library function to paint the row backgroung when slected
    void paintRowBackground(Graphics&,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;

    //juce library function to paint each cell when any new row is added in our main track-vector
    void paintCell(Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;

    //juce library function to add play dynamic play button infront of each track
    Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool isRowSelected,
        Component* existingComponentToUpdate) override;

    //juce library function, which is called everytime when any button is clicked
    void buttonClicked(Button* button) override;

    //function for the load button to open file explorer and select the prefered song
    void import_library();
    
private:

    TextButton load_Button{ "LOAD A PARTICULAR TRACK" }; //load button object
    
    TableListBox tableComponent; //juce library table component, which will contain our current playlist
    
    void select_file(juce::File o_file); //function to push track details into out track vectors
    
    double return_song_length(juce::URL our_audio); //function to return the each song length in seconds
    
    void save_our_data(); //function to save our current user playlist before program closes
    
    void search_the_track(juce::String our_text); //function for the search button, performing linear search
    
    void load_the_track(); //function to load all the trck saved in our notepad file
    
    DeckGUI* deck_1;  //creating instance of deck_1
    
    DeckGUI* deck_2; //creating instance of deck_2
    
    std::fstream file; //creating file variable to store everything in notepad
    
    juce::TextEditor search_area; //search box object
    
    DJAudioPlayer* player_extra_DJAudioPlayer; //creating instance of DJAudioPlayer
    
    std::vector<std::string> trackTitles; //vector storing the each song name
    
    std::vector<std::string> tracklength; //vector storing the each song length
    
    std::vector<juce::URL> our_song_list_url; //vector storing the URL of each song
   
    int c_1; //our global counter variable
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent) //juce library Macro
};
