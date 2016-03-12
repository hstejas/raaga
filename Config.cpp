#include "Config.h"
#include <sstream>


namespace bo = boost::program_options;
Config::Config()
:_options("Options")
{
    _options.add_options()
    ("MAIN.VOLUME", bo::value<std::string>(), "Volume between 0.0 to 1.0")
    ("PLAYING.LIST", bo::value<std::string>(), "playlist file")
    ;
}

bool Config::load(const std::string& configFile)
{
    std::ifstream ifs(configFile.c_str());
    if (!ifs)
    {
        std::cout << "can not open config file: " << configFile << "\n";
        return false;
    }
    else
    {
        bo::store(bo::parse_config_file(ifs, _options), _vm);
        bo::notify(_vm);
    }
}

void Config::dump()
{
    for(auto it = _vm.begin(); it != _vm.end(); it++)
    {
        std::cout << (*it).first << "=" << get<std::string>((*it).first) << std::endl;
    }
}

template<typename RET>
RET Config::get(const std::string& opt) const
{
    std::istringstream os(_vm[opt].as< std::string >());
    RET ret;
    os >> ret;
    return ret;
}