#include "Raaga.h"

Raaga::Raaga(int &argc, char*** argv)
{
    _cfg.load("raaga.cfg");
    _cfg.dump();
    _player = std::make_shared<GstPlayer>();
    _io = std::make_shared<ConsoleIO>();
    _player->init(argc, argv);
}

bool Raaga::loadList()
{
    std::ifstream fin(_cfg.get<std::string>("PLAYING.LIST"));
    if(fin)
    {
        std::string line;
        while(std::getline(fin, line))
        {
            std::streampos pos = line.find_first_of(";");
            NameUriPair uriPair = NameUriPair(line.substr(0LL,pos) , line.substr(pos+1LL,line.length()));            
            std::cout << uriPair.first << "  --  " << uriPair.second << std::endl;
            _list.push_back(uriPair);
        }
        
        if(_list.size() > 0)
        {
            _listIt = _list.begin();
        }
        else 
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}

void Raaga::run()
{
    bool quit(false);
    while(!quit)
    {
        Instruction inst = _io->getInstruction();
        switch(inst)
        {
            case Instruction::PLAY: 
                _player->play(_listIt->second);
                _io->sendState(State::PLAYING);
                break;
            case Instruction::PAUSE:
                _player->pause();
                _io->sendState(State::PAUSED);
                break;
            case Instruction::STOP:
                _player->stop();
                _io->sendState(State::STOPPED);
                break;
            case Instruction::QUIT:
                _player->quit();
                _io->sendState(State::QUITTING);
                quit = true;
                break;
            case Instruction::VOLUME_UP:
                _player->setVolume(_player->getVolume()+0.05);
                _io->sendState(State::VOLUME_SET);
                break;
            case Instruction::VOLUME_DOWN:
                _player->setVolume(_player->getVolume()-0.05);
                _io->sendState(State::VOLUME_SET);
                break;
            case Instruction::MUTE:
                _player->setMute(!_player->getMute());
                _io->sendState(State::MUTE);
                break;
            case Instruction::NEXT:
                _player->stop();
                _listIt = _listIt == _list.end()-1? _list.begin() : _listIt+1;
                _player->play(_listIt->second);
                _io->sendState(State::PLAYING);
                break;
            case Instruction::PREVIOUS:
                _player->stop();
                _listIt = _listIt == _list.begin()? _list.end()-1 : _listIt-1;
                _player->play(_listIt->second);
                _io->sendState(State::PLAYING);
                break;
            default:
                _io->sendState(State::ERROR);
                break;
        }        
    }
    
}
