////!@file Driver.cpp
////!  @brief Displays the functionality of the builder pattern for maps 
////!
////!  The functionality is demonstrated by first loading and displaying a map
////!  The monsters and treaure within the map are then displayed. The functionality is 
////!  demonstrated for both the SaveMapBuilder and the LevelMapBuilder
////!  In a map: e denotes empty space, t is treasure and m is monster.
////!  @Author Connor Young 40006914
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <vector>
//#include "Map.h"
//#include "MapDirector.h"
//#include "MapBuilder.h"
//#include "MapSaveBuilder.h"
//#include "LevelMapBuilder.h"
//#include "Helmet.h"
//#include "Armor.h"
//#include "Belt.h"
//#include "Ring.h"
//#include "Shield.h"
//#include "Weapon.h"
//#include "Boots.h"
//#include "ItemGenerator.h"
//using namespace std;
//
//void main()
//{
//	cout << "Using MapSaveBuilder\n";
//	// Build the map using the builder pattern
//	MapDirector mapDirector;
//	MapSaveBuilder* mapSaveBuilder = new MapSaveBuilder();
//	mapDirector.setMapBuilder(mapSaveBuilder);
//	mapDirector.constructMap("map.txt");
//	Map* map = mapSaveBuilder->getMap();
//
//	// Print the map
//	cout << "\nMap Created from map.txt";
//	map->printMap();
//
//
//	// Retrieve the monsters on the map and print the count
//	vector<Monster>* monsters = mapSaveBuilder->getMonsters();
//	cout << "\nMonster count: " << monsters->size();
//	mapSaveBuilder->printMonsters(monsters);
//
//	// Retrieve the treasures on the map and print the count
//	vector<vector<Item>>* treasureList = mapSaveBuilder->getTreasure();
//	cout << "\n\nTreasure count: " << treasureList->size();
//	// Items are contained within the treasure
//	mapSaveBuilder->printTreasure(treasureList);
//
//
//	cout << "\n\nUsing LevelMapBuilder \n";
//	// Builder the map using builder pattern and level 5
//	LevelMapBuilder* lmb = new LevelMapBuilder(5);
//	mapDirector.setMapBuilder(lmb);
//	mapDirector.constructMap("map.txt");
//	map = lmb->getMap();
//
//	// Print the map
//	cout << "\nMap Created from map.txt";
//	map->printMap();
//
//	// Retrieve the monsters on the map and print the count
//	monsters = lmb->getMonsters();
//	cout << "\nMonster count: " << monsters->size();
//	mapSaveBuilder->printMonsters(monsters);
//
//	// Retrieve the treasures on the map and print the count
//	treasureList = lmb->getTreasure();
//	cout << "\n\nTreasure count: " << treasureList->size();
//	// Items are contained within the treasure
//	mapSaveBuilder->printTreasure(treasureList);
//}
//
