#ifndef RAAGA_RAAGA_MAIN_H
#define RAAGA_RAAGA_MAIN_H

#include<memory>
#include<vector>
#include<string>
#include "Config.h"
#include "DefaultIO.h"
#include "GstPlayer.h"

class Raaga
{
public:
    Raaga(int &argc, char*** argv);    
    void run();
    bool loadList();
    
protected:
    Config _cfg;
    std::shared_ptr<GstPlayer> _player;
    std::shared_ptr<IInOut> _io;
    typedef std::pair<std::string, std::string> NameUriPair;
    std::vector<NameUriPair> _list;
    std::vector<NameUriPair>::iterator _listIt;
};


#endif //RAAGA_RAAGA_MAIN_H