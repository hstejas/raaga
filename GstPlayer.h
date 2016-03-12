#ifndef RAAGA_GST_PLAYER_H
#define RAAGA_GST_PLAYER_H

#include <iostream>
#include <gst/gst.h>
#include <string>
#include <thread>
#include "IMediaPlayer.h"

class GstPlayer : public IMediaPlayer
{
public:
    GstPlayer() : _isLooping(false){    }
    
    void init(int &argc, char ***argv);

    virtual void play(const std::string& uri);
    
    virtual void pause();
    
    virtual void stop();   
    
    virtual void quit();
    
    virtual double getVolume();
    
    virtual void setVolume(double);
    
    virtual void setMute(bool);

    virtual bool getMute();
    
    virtual ~GstPlayer();

protected:
    virtual void addBus();

    virtual void runLoop();
    
    static gboolean my_bus_callback (GstBus *bus, GstMessage *msg, gpointer data);

    GMainLoop *_loop;
    GstElement *_playElem;
    std::thread _mainLoop;
    bool _isLooping;
};

/*
int main(int argc, char** argv)
{
    std::cout << "enter URI: ";
    std::string uri;
    std::getline(std::cin , uri);
    GstPlayer GstPlayer;
    GstPlayer.init(argc, &argv);
    std::string command;
    while(std::getline(std::cin, command))
    {
        if(command.find("pl") != std::string::npos)
        {
            GstPlayer.play(uri);
            std::cout << "playing...\n";
        }
        else if(command.find("pa") != std::string::npos)
        {
            GstPlayer.pause();
        }
        else if(command.find("qu") != std::string::npos)
        {
            GstPlayer.quit();
            break;
        }
        else
        {
            std::cout << "unknown command\n";
        }
    }    
}
*/
#endif //RAAGA_GST_PLAYER_H