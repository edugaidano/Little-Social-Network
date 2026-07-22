#include "config.h"

CONFIG_D get_config_dictionary(std::string config_path) {
    std::ifstream config_file(config_path);
    if (!config_file.is_open()) {
        std::cerr<<"The config file could not be open\n";
        exit(EXIT_FAILURE);
    }

    std::string line;
    std::map<std::string, std::string> config_settings;
    while (std::getline(config_file, line))  {
        size_t delimiter = line.find("=");
        if (delimiter != std::string::npos) {
            std::string key = line.substr(0, delimiter);
            std::string value = line.substr(delimiter + 1);
            config_settings[key] = value;
        }   
    }
    config_file.close();
    return config_settings;
}

void update_config_dictionary(std::string config_path, CONFIG_D new_config) {
    std::ofstream config_file(config_path);
    if (!config_file.is_open()) {
        std::cerr<<"The config file could not be open\n";
        exit(EXIT_FAILURE);
    }
    for (const auto& pair : new_config) {
        config_file << pair.first << "=" << pair.second << "\n";
    }
    config_file.close();
}