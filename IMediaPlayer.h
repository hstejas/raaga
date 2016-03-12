#ifndef RAAGA_MEDIA_PLAYER_INTERFACE_H
#define RAAGA_MEDIA_PLAYER_INTERFACE_H

class IMediaPlayer
{
public:    
    virtual void play(const std::string& uri) = 0;
    
    virtual void pause() = 0;
    
    virtual void stop() = 0;
    
    virtual void quit() = 0;
    
    virtual double getVolume() = 0;
    
    virtual void setVolume(double) = 0;
    
    virtual void setMute(bool) = 0;
    
    virtual bool getMute() = 0;
    
    virtual ~IMediaPlayer(){};
};

#endif //RAAGA_MEDIA_PLAYER_INTERFACE_H
