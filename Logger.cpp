#include "Logger.h"
#include <string>
#include <iostream>
#include <fstream>


Logger::Logger()
{
	gameLogOn = true;
	mapLogOn = true;
	characterLogOn = true;
	diceLogOn = true;
}


Logger::~Logger()
{
}

void Logger::LogGame(std::string message)
{
	if (gameLogOn) {
		std::ofstream outputFile;
		outputFile.open("Log.txt", std::ios_base::app);

		outputFile << "Type: GAME || " << message << std::endl;

		outputFile.close();
	}
}

void Logger::LogMap(std::string message)
{
	if (mapLogOn) {
		std::ofstream outputFile;
		outputFile.open("Log.txt", std::ios_base::app);

		outputFile << "Type: MAP || " << message << std::endl;

		outputFile.close();
	}
}

void Logger::LogCharacter(std::string message)
{
	if (characterLogOn) {
		std::ofstream outputFile;

		outputFile.open("Log.txt", std::ios_base::app);

		outputFile << "Type: Character || " << message << std::endl;

		outputFile.close();
	}

}

void Logger::LogDice(std::string message)
{
	if (diceLogOn) {
		std::ofstream outputFile;
		outputFile.open("Log.txt", std::ios_base::app);

		outputFile << "Type: DICE || " << message << std::endl;

		outputFile.close();
	}
}
