#include "FileReader.hpp"
#include <sstream>
#include <crtdbg.h>

bool FileReader::open(const std::string& filename)
{
    return sf::FileInputStream::open(filename);
}

bool FileReader::readAll(std::vector<char>& buffer)
{
    buffer.resize(getSize());
    return read(&buffer[0], buffer.size()) != 0;
}

