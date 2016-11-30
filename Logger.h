#pragma once
#include <string>
//! @file Logger.h
//! @brief Class that will handle all types of logging during the game. Examples of such are game component initialization and setup,
//! character position on the map after every move, character combat sequence, dice rolls, and much more.
class Logger
{
public:
	Logger();
	~Logger();

	//! Will write a game message to file
	//! @param message	Message to be logged
	void LogGame(std::string message);

	//! Will write a map message to file
	//! @param message	Message to be logged
	void LogMap(std::string message);

	//! Will write a character message to file
	//! @param message	Message to be logged
	void LogCharacter(std::string message);

	//! Will write a dice message to file
	//! @param message	Message to be logged
	void LogDice(std::string message);

	//! Toggle the game log to on and off. True = On, False = Off
	//! @param state	State of logger
	void setGameLog(bool state) { gameLogOn = state; }

	//! Toggle the map log to on and off. True = On, False = Off
	//! @param state	State of logger
	void setMapLog(bool state) { mapLogOn = state; }

	//! Toggle the character log to on and off. True = On, False = Off
	//! @param state	State of logger
	void setCharacterLog(bool state) { characterLogOn = state; }

	//! Toggle the dice log to on and off. True = On, False = Off
	//! @param state	State of logger
	void setDiceLog(bool state) { diceLogOn = state; }
private:
	bool gameLogOn; // Whether game related events will be logged
	bool mapLogOn;  // Whether map related messages will be logged
	bool characterLogOn;  // Whether character and combat related messages will be logged
	bool diceLogOn;  // Whether dice rolls will be logged
};

