/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 30 Aug 2022 2:31:45am
    Author:  rishi

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI* _deck_1, DeckGUI* _deck_2,DJAudioPlayer* _player_extra_DJAudioPlayer) : 
                        deck_1(_deck_1),
                        deck_2(_deck_2),
                        player_extra_DJAudioPlayer(_player_extra_DJAudioPlayer)
{
    load_the_track();
    c_1 = 0;
    tableComponent.getHeader().addColumn("Track title", 0, 250);
    tableComponent.getHeader().addColumn("length in sec", 1, 100);
    tableComponent.getHeader().addColumn("disk 1", 2, 50);
    tableComponent.getHeader().addColumn("disk 2", 3, 50);
    tableComponent.setModel(this);
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(load_Button);
    addAndMakeVisible(search_area);
    load_Button.addListener(this);
    search_area.addListener(this);
    search_area.setTextToShowWhenEmpty("search your track here",juce::Colours::white);
    search_area.onReturnKey = [this] { 
        search_the_track(search_area.getText()); 
    };
}

PlaylistComponent::~PlaylistComponent()
{
    save_our_data();
}

void PlaylistComponent::paint (Graphics& g)
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
    g.drawText ("PlaylistComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 0, getWidth(), (getHeight()/10)*8);
    search_area.setBounds(0, (getHeight() / 10) * 8, getWidth(), (getHeight() / 10) * 1);
    load_Button.setBounds(0, (getHeight() / 10) * 9, getWidth(), (getHeight() / 10) * 1);
}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size(); // we'll have three rows for now
}

//function to paint row background
void PlaylistComponent::paintRowBackground(Graphics& g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    // just highlight selected rows
    if (rowIsSelected)
    {
        g.fillAll(Colours::blue);
    }
    else {
        g.fillAll(Colours::white);
    }
}

//function to paint each cell
void PlaylistComponent::paintCell(Graphics& g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{
    if (rowNumber < getNumRows())
    {
        if (columnId == 0) //painting the first column data
        {
            g.drawText(trackTitles[rowNumber],
                2,
                0,
                width - 4,
                height,
                juce::Justification::centredLeft,
                true
            );
        }
        if (columnId == 1) //painting the second column data
        {
            g.drawText(tracklength[rowNumber],
                2,
                0,
                width - 4,
                height,
                juce::Justification::centred,
                true
            );
        }
    }
}

//function to add dynamic buttons
Component* PlaylistComponent::refreshComponentForCell(
    int rowNumber,
    int columnId,
    bool isRowSelected,
    Component* existingComponentToUpdate)
{
    if (columnId == 2)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton("play");
            String id{ std::to_string(c_1) };
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
            c_1 = c_1 + 1;
        }
    }
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton("play");
            String id{ std::to_string(c_1) };
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
            c_1 = c_1 + 1;
        }
    }
    return existingComponentToUpdate;
}

//button clicked function, which extracts the button id and add the track to respected deck
void PlaylistComponent::buttonClicked(Button* button)
{
    //code for non dynamic buttons
    if(button == &load_Button)
    {
        std::cout << "Play button was clicked " << std::endl;
        import_library();
        tableComponent.updateContent();
        DBG(button->getComponentID());
    }
    //code for dynamic buttons
    else {
        int id = std::stoi(button->getComponentID().toStdString());
        if (id % 2 == 0) {
            if (id == 0) {
                deck_1->loadthecurrentfile(our_song_list_url[id]);
            }
            else {
                deck_1->loadthecurrentfile(our_song_list_url[id/2]);
            } 
        }
        else {
            if (id == 1) {
                deck_2->loadthecurrentfile(our_song_list_url[id-1]);
            }
            else {
                deck_2->loadthecurrentfile(our_song_list_url[(id - 1)/2]);
            }
        }
    }
}

//function to open file browser
void PlaylistComponent::import_library()
{
    FileChooser chooser{"Select a file..."};
    if (chooser.browseForFileToOpen())
    {
        select_file(chooser.getResult());
    }
}

//function to add the selected file to our vectors
void PlaylistComponent::select_file(juce::File o_file)
{
    trackTitles.push_back(o_file.getFileNameWithoutExtension().toStdString());
    juce::URL our_audio{ o_file};
    our_song_list_url.push_back(our_audio);
    tracklength.push_back(std::to_string(return_song_length(our_audio)));
    DBG(o_file.getFileNameWithoutExtension().toStdString());
}

//function which returns track length in seconds
double PlaylistComponent::return_song_length(juce::URL our_audio)
{
    player_extra_DJAudioPlayer->loadURL(our_audio);
    double seconds{ player_extra_DJAudioPlayer->return_current_length() };
    return seconds;
}

//function to save our current playlist to a note pad file
void PlaylistComponent::save_our_data()
{
    int c = 0;
    file.open("our_loaded_track_data.txt", std::ios_base::out);
    for (auto& element : trackTitles) 
    {
        if (c < tracklength.size()-1) 
        {
            file << element;
            file << std::endl;
            file << tracklength[c];
            file << std::endl;
            file << our_song_list_url[c].toString(false);
            file << std::endl;
        }
        else 
        {
            file << element;
            file << std::endl;
            file << tracklength[c];
            file << std::endl;
            file << our_song_list_url[c].toString(false);
        }
        c++;
    }
    file.close();
}

//function for the search button
void PlaylistComponent::search_the_track(juce::String our_text)
{
    if (our_text != "")
    {
        int c = 0;
        for (auto& element : trackTitles) 
        {
            std::size_t found = element.find(our_text.toStdString());
            if (found != std::string::npos)
                tableComponent.selectRow(c); //select row according to the searched results
            c++;
        } 
    }
    else
    {
        tableComponent.deselectAllRows();
    }
}

//function to load our saved playlist
void PlaylistComponent::load_the_track()
{
    int c = 0;
    std::ifstream input("our_loaded_track_data.txt");
    for (std::string line; getline(input, line); )
    {
        if (c % 3 == 0) {
            trackTitles.push_back(line);
        }
        if(c % 3 == 1) {
            tracklength.push_back(line);
        }
        if (c % 3 == 2) {
            juce::URL our_audio{ line };
            our_song_list_url.push_back(our_audio);
        }
        c++;
    }
    tableComponent.updateContent();
}

//end code
