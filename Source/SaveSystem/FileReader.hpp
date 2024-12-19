#pragma once

#include "SFML/System/FileInputStream.hpp"

class FileReader : public sf::FileInputStream
{
public:

    //open file for reading
    bool open(const std::string& filename);

    //read file and 
    std::string readAll();

};