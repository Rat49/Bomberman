#include "FileWriter.hpp"

bool FileWriter::open(const std::string& filePath)
{
    m_fileStream.open(filePath, std::ios::binary, std::ios::trunc);
    return m_fileStream.is_open();
}

void FileWriter::write(const std::string& data)
{
    if (m_fileStream.is_open())
    {
        m_fileStream.write(data.c_str(), data.size());
    }
}

void FileWriter::close()
{
    if (m_fileStream.is_open())
    {
        m_fileStream.close();
    }
}


