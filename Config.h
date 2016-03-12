#ifndef RAAGA_CONFIG_H
#define RAAGA_CONFIG_H

#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <string>

class Config
{
public:
    Config();
    virtual bool load(const std::string& configFile);
    virtual void dump();
    template<typename RET>
    RET get(const std::string& ) const;

protected:
    boost::program_options::options_description _options;
    boost::program_options::variables_map _vm;
};

#endif //RAAGA_CONFIG_H