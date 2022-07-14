// DataManager.cpp : Define las funciones de la biblioteca estática.
// BE AWARE! Los archivos de mapas y prefabs deben guardarse en el directorio resources del directorio exes del proyecto.

#include "DataManager.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <map>

//Reads a .json file ande parses it to a json class instance
json DataManager::ReadJson(const std::string& file_name) {
	json j;
	std::ifstream input;
	//AUX
	std::string s;
	s = relativeResourcesPath+"gameFiles/" + file_name;
	input.open(s);

	input >> j;

	input.close();
	return j;
}

std::vector<std::vector<std::string>> DataManager::ReadMap(const std::string& file_name) {
	std::vector<std::vector<std::string>> map;
	std::ifstream input;
	//AUX
	std::string s;

	s = relativeResourcesPath+ "gameFiles/" + file_name;
	input.open(s);
	s.clear();

	while (!input.eof()) {
		//Si la siguiente linea se debe leer..
		if (ReadNext(input))
		{
			getline(input, s);
			map.push_back(GetWords(s));
		}
		else
		{
			getline(input, s);
		}
	}

	input.close();
	return map;
}

//Outputs on console a readable debug of a json file
void DataManager::DebugJson(json json_file) {
	std::cout << '\n' << "---------------------------------------JsonDebug-Start--------------------------------------" << '\n';

	std::cout << "Debugging " << json_file.begin().key() << " file... " << '\n' << '\n';
	json_file = json_file.at(json_file.begin().key());

	//For each object in the file...
	for (std::size_t i = 0; i < json_file.size(); i++) {
		std::cout << "----------------------" << '\n';
		std::cout << "Entity: " << json_file[i].at("id") << '\n';						//Entity type

		std::cout << "Components :" << '\n';
		//For each element  in the object...
		if (!json_file[i].at("components").size())
		{
			std::cout << "\"None\"" << '\n';
		}
		else
		{
			//For each  component in components[]...
			for (std::size_t j = 0; j < json_file[i].at("components").size(); j++)
			{
				std::cout << '*' << json_file[i].at("components")[j].at("id") << '*' << '\n'; 	//Component type
				std::cout << json_file[i].at("components")[j] << '\n';								//Component description
			}
		}

		std::cout << "----------------------" << '\n';
	}
	std::cout << '\n' << "---------------------------------------JsonDebug-End--------------------------------------" << '\n';
}

void DataManager::DebugMap(std::vector<std::vector<std::string>> map, bool output_debugTxt) {
	std::ofstream output;
	time_t now = time(0);
	char dateTime[26];
	std::string d_file_name;

	if (output_debugTxt) {
		d_file_name = "resources/gameFiles/mapDebugs/debug_map_";
		ctime_s(dateTime, sizeof(dateTime), &now);

		int i = 0;
		bool end = false;
		while (!end && i < sizeof(dateTime)) {
			if (dateTime[i] == '\n') {
				end = true;
			}

			else if (dateTime[i] == ' ') {
				dateTime[i] = '_';
			}

			else if (dateTime[i] == ':') {
				dateTime[i] = '-';
			}
			
			if (!end) {
				d_file_name += dateTime[i];
				i++;
			}	
		}
		d_file_name += ".txt";

		std::cout << '\n' << "---------------------------------------MapDebug-Start--------------------------------------" << '\n';
		std::cout << "Map debug file created at: " << d_file_name << "\n";

		output.open(d_file_name);
	}

	for (auto i = map.begin(); i != map.end(); i++) {	
		if (output_debugTxt)
			output << "--------------------------------------" << '\n';
		std::cout << "--------------------------------------" << '\n';

		for (auto j = i->begin(); j != i->end(); j++)
		{
			if (output_debugTxt)
				output << j->c_str() << '|';
			std::cout << j->c_str() << '|';
		}
		if (output_debugTxt)
			output << '\n' << "--------------------------------------" << '\n';
		std::cout << '\n' << "--------------------------------------" << '\n';
	}
	std::cout << '\n' << "---------------------------------------MapDebug-End--------------------------------------" << '\n';
	if (output_debugTxt)
		output.close();
}

bool DataManager::ReadNext(std::ifstream& input) {
	char c;
	c = input.peek();

	//Si es un salto de línea -> no lee 
	if (c == '\n')
		return false;

	//Si es un comentario -> no lee
	else if (c == '/')
	{
		input.get();
		c = input.peek();
		if (c == '/') 
			return false;		
	}

	//En cualquier otro caso si lee
	return true;
}

std::vector<std::string> DataManager::GetWords(std::string& s) {
	std::vector<std::string> words;
	std::string word;
	for (auto x : s)
	{
		if (x == ' ')
		{
			words.push_back(word);
			word = "";
		}
		else
		{
			word = word + x;
		}
	}
	words.push_back(word);
	return words;
}
