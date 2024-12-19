#include "FileReader.hpp"
#include <sstream>

bool FileReader::open(const std::string& filename)
{
    return sf::FileInputStream::open(filename);
}

std::string FileReader::readAll()
{
    std::ostringstream content;

    sf::Int64 size = getSize();
    auto buffer = std::make_unique<char[]>(size);
    
    read(buffer.get(), size);
    
    content.write(buffer.get(), size);
    
    return content.str();
}
