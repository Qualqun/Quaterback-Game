#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

class Logger
{
public:
	Logger();
	Logger(std::ostream& _stream, std::string _name);
	Logger(const Logger& _logger);
	~Logger();

	// Prints a "LOG" typed message
	void Log(const std::string _message);

	// Prints a "WARNING" typed message
	void Warning(const std::string _message);

	// Prints a "ERROR" typed message
	void Error(const std::string _message);

	// Prints a "SUCCESS" typed message
	void Success(const std::string _message);

	// Prints a "DEBUG" typed message, only visible during a debug phase
	void Debug(const std::string _message);

	// Returns the std::ostream reference object used by the Logger
	std::ostream& GetLogger();

	// Returns the Logger's name
	std::string GetLoggerName();

private:
	std::ostream& m_stream = std::cout;
	std::string m_loggerName = "Logger";

	void Message(const std::string, const std::string);
};

#endif