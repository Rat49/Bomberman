#pragma once
#include "LogModule/BaseLogListener.hpp"
#include <fstream>


class FileLogListener : public BaseLogListener
{
public:
	FileLogListener(const std::string& path, const uint16_t& levelMask, const uint16_t& channelMask)
		: BaseLogListener(levelMask, channelMask), mFilePath(path)
	{
		mFileStream = std::ofstream(path);
	}

	~FileLogListener()
	{
		mFileStream.close();
	}

private:
	std::string mFilePath;
	std::ofstream mFileStream;

	void Write(const std::string& text) override
	{
		mFileStream << text << "\n";
	};
};
