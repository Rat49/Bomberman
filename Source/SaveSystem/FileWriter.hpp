#pragma once

#include <fstream>

class FileWriter
{
public:

    //opens a file for writing
    bool open(const std::string& filePath);

    //writes the given data to the file
    void write(const std::string& data);

    //close file
    void close();

private:
    std::ofstream m_fileStream;
};
