#ifndef _CONFIG_HPP
#define _CONFIG_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <map>

typedef std::map<std::string, std::string> CONFIG_D;

CONFIG_D get_config_dictionary(std::string config_path);
void update_config_dictionary(std::string config_path, CONFIG_D new_config);

#endif