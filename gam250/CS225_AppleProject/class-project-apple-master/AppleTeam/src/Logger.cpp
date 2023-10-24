/************************************************************************
*	File name : Logger.cpp
*	Project name : apple
*	Author	    Primary author : Seungguk Jang
*			    Secondary author : Junseok Yang
*	File description : Give log level (high priority)Error->event->debug->verbose(low priority)
*	2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
#include "Logger.h"

void Logger::Log(Severity severity, std::string displayText) noexcept
{
	if (severity >= severityLevel)
	{
		switch (severity)
		{
		case Logger::Severity::VERBOSE:
			std::cout << "VERBOSE : " << displayText << std::endl;
			break;
		case Logger::Severity::DEBUG:
			std::cout << "DEBUG : " << displayText << std::endl;
			break;
		case Logger::Severity::EVENT:
			std::cout << "EVENT : " << displayText << std::endl;
			break;
		case Logger::Severity::ERROR:
			std::cout << "ERROR : " << displayText << std::endl;
			break;
		}
	}
}

void Logger::Log(Severity severity, float displayNumber) noexcept
{
	if (severity >= severityLevel)
	{
		switch (severity)
		{
		case Logger::Severity::VERBOSE:
			std::cout << "VERBOSE : " << displayNumber << std::endl;
			break;
		case Logger::Severity::DEBUG:
			std::cout << "DEBUG : " << displayNumber << std::endl;
			break;
		case Logger::Severity::EVENT:
			std::cout << "EVENT : " << displayNumber << std::endl;
			break;
		case Logger::Severity::ERROR:
			std::cout << "ERROR : " << displayNumber << std::endl;
			break;
		}
	}
}

void Logger::Log(Severity severity, int displayNumber) noexcept
{
	if (severity >= severityLevel)
	{
		switch (severity)
		{
		case Logger::Severity::VERBOSE:
			std::cout << "VERBOSE : " << displayNumber << std::endl;
			break;
		case Logger::Severity::DEBUG:
			std::cout << "DEBUG : " << displayNumber << std::endl;
			break;
		case Logger::Severity::EVENT:
			std::cout << "EVENT : " << displayNumber << std::endl;
			break;
		case Logger::Severity::ERROR:
			std::cout << "ERROR : " << displayNumber << std::endl;
			break;
		}
	}
}