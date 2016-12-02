#include "CharacterListings.h"
#include "Logger.h"


CharacterListings::CharacterListings()
{
	getCharacterPathNames();
}


CharacterListings::~CharacterListings()
{

}

Character* CharacterListings::acceptInput4Character() {
	int index = 0;

	bool screwingUp = true;
	while (screwingUp) {
		std::cout << "\nEnter the number of the character you want: \n";
		char input[9001] = "";
		std::cin >> input;
		index = atoi(input) - 1;
		if (index == -1) std::cout << input << " isn't a character...\n";
		else if (index + 1 > pathNames.size()) std::cout << input << " is going to crash the game...\n";
		else {
			std::cout << "Number " << input << " is a pretty strong...\n";
			screwingUp = false;
		}
	}
	std::cout << "\n";
	CharacterDriver cd;
	Logger log;
	log.LogCharacter("User selected Character " + pathNames.at(index));
	return cd.load(pathNames.at(index));
}

void CharacterListings::displayCharacters() {
	int count = 1;
	for each(std::string chararacter in pathNames) {
		std::string name = pathNames.at(count - 1);
		name.resize(name.size() - 4);
		name.erase(name.begin(), name.begin() + 13);
		std::cout << count << ". " << name << std::endl;
		count++;
	}
}

#include <windows.h>
void CharacterListings::getCharacterPathNames() {

	WIN32_FIND_DATAA characterFile;
	HANDLE directoryToSearch = FindFirstFileA("./Characters/*", &characterFile);

	std::cout << "\n\nSearching Character Directory\n";
	if (directoryToSearch)
	{
		do
		{
			std::cout << characterFile.cFileName << std::endl;
			std::string localPath = characterFile.cFileName;
			if (localPath != "." && localPath != "..")
				pathNames.push_back("./Characters/" + localPath);
		} while (FindNextFileA(directoryToSearch, &characterFile));
	}
	else std::cout << "Directory ./Characters/* could not be found\n";
	std::cout << "\n";
}

int CharacterListings::getNumberOfOptions() {
	return pathNames.size();
}