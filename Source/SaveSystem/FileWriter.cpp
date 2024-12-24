#include "FileWriter.hpp"
#include <Common/Logs.hpp>

FileWriter::~FileWriter()
{
    if (m_file)
    {
        std::fclose(m_file);
    }
}

bool FileWriter::open(const std::string& filePath, bool append)
{
    fopen_s(&m_file, filePath.c_str(), append ? "ab" : "wb");
    return m_file != nullptr;
}

bool FileWriter::write(const std::vector<char> data)
{
    if (m_file)
    {
        std::size_t written = std::fwrite(data.data(), 1, data.size(), m_file);
        return written == data.size();
    }
    return false;
}