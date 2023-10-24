/************************************************************************
*	File name : Logger.h
*	Project name : apple
*	Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Give log level (high priority)Error->event->debug->verbose(low priority)
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <type_traits>

class [[nodiscard]] Logger {
public:
	enum class Severity {
		VERBOSE,		
		DEBUG,			
		EVENT,			
		ERROR,			
	};
	Logger(Severity severity, bool useConsole) noexcept : severityLevel(severity), outStream("Trace.log") {
		if (useConsole == true) {
			outStream.set_rdbuf(std::cout.rdbuf());
		}
	} 

	template< bool B, class T = void >
	using enable_if_t = typename std::enable_if<B, T>::type;

	template<typename T>
	struct is_string : public std::disjunction<std::is_same<const char*, typename std::decay_t<T>>,
		std::is_same<std::string, typename std::decay_t<T>>> {};

	template <typename STRING>
	enable_if_t<is_string<STRING>::value, STRING> LogError(STRING v)
	{
		Log(Severity::ERROR, v);
		return v;
	}
	template <typename STRING>
	typename std::enable_if<is_string<STRING>::value, STRING>::type LogEvent(STRING v)
	{
		Log(Severity::EVENT, v);
		return v;
	}
	template <typename STRING>
	enable_if_t<is_string<STRING>::value, STRING> LogDebug(STRING v)
	{
		Log(Severity::DEBUG, v);
		return v;
	}
	template <typename STRING>
	typename std::enable_if<is_string<STRING>::value, STRING>::type LogVerbose(STRING v)
	{
		Log(Severity::VERBOSE, v);
		return v;
	}

	template <typename FLOAT>
	typename std::enable_if<std::is_floating_point<FLOAT>::value, FLOAT>::type LogError(FLOAT v)
	{
		Log(Severity::ERROR, v);
		return v;
	}
	template <typename FLOAT>
	typename std::enable_if<std::is_floating_point<FLOAT>::value, FLOAT>::type  LogEvent(FLOAT v)
	{
		Log(Severity::EVENT, v);
		return v;
	}
	template <typename FLOAT>
	typename std::enable_if<std::is_floating_point<FLOAT>::value, FLOAT>::type  LogDebug(FLOAT v)
	{
		Log(Severity::DEBUG, v);
		return v;
	}
	template <typename FLOAT>
	typename std::enable_if<std::is_floating_point<FLOAT>::value, FLOAT>::type  LogVerbose(FLOAT v)
	{
		Log(Severity::VERBOSE, v);
		return v;
	}

	template <typename INT>
	typename std::enable_if<std::is_integral<INT>::value, INT>::type LogError(INT v)
	{
		Log(Severity::ERROR, v);
		return v;
	}
	template <typename INT>
	typename std::enable_if<std::is_integral<INT>::value, INT>::type  LogEvent(INT v)
	{
		Log(Severity::EVENT, v);
		return v;
	}
	template <typename INT>
	typename std::enable_if<std::is_integral<INT>::value, INT>::type  LogDebug(INT v)
	{
		Log(Severity::DEBUG, v);
		return v;
	}
	template <typename INT>
	typename std::enable_if<std::is_integral<INT>::value, INT>::type  LogVerbose(INT v)
	{
		Log(Severity::VERBOSE, v);
		return v;
	}

	~Logger() {}
private:
	void Log(Severity, std::string displayText) noexcept;
	void Log(Severity, float displayNumber) noexcept;
	void Log(Severity, int displayNumber) noexcept;
	std::ofstream outStream;
	Severity severityLevel;
};