#pragma once

#include <vector>
#include <string>

class FileWriter
{
public:

    //destructor to close file
    ~FileWriter();

    //opens a file for writing
    bool open(const std::string& filePath, bool append = false);

    //writes the given data to the file
    bool write(const std::vector<char> data);

private:

    std::FILE* m_file;
};
