#include "Logger.hpp"

#include <chrono>
#include <ctime> 

Logger::Logger() : m_stream(std::cout) {}

Logger::Logger(std::ostream& _stream, std::string _name) : m_stream(_stream), m_loggerName(_name) {}

Logger::Logger(const Logger& _logger) : m_stream(_logger.m_stream) {}

Logger::~Logger() {}

std::ostream& Logger::GetLogger()
{
	return this->m_stream;
}

std::string Logger::GetLoggerName()
{
	return this->m_loggerName;
}

void Logger::Message(const std::string _type, const std::string _message)
{
	std::time_t time = std::time(0);
	std::tm* now = new std::tm;
	localtime_s(now, &time);

	m_stream << "[" << (now->tm_year + 1900) << "/" << (now->tm_mon + 1) << "/" << (now->tm_mday) << " " <<
		(now->tm_hour) << "." << (now->tm_min) << "." << (now->tm_sec) << "] " << this->GetLoggerName() << " | " <<
		_type << " : " << _message << std::endl;
}

void Logger::Log(const std::string _message)
{
	this->Message("LOG", _message);
}

void Logger::Warning(const std::string _message)
{
	this->Message("WARNING", _message);
}

void Logger::Error(const std::string _message)
{
	this->Message("ERROR", _message);
}

void Logger::Success(const std::string _message)
{
	this->Message("SUCCESS", _message);
}

void Logger::Debug(const std::string _message)
{
#ifdef _DEBUG
	this->Message("DEBUG", _message);
#endif
}