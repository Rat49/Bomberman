#pragma once

#include "SFML/System/FileInputStream.hpp"
#include <vector>

class FileReader : public sf::FileInputStream
{
public:

    //open file for reading
    bool open(const std::string& filename);

    //read file and 
    bool readAll(std::vector<char>& buffer);
};