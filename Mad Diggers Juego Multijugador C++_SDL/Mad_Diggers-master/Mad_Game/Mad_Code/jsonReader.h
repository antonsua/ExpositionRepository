#pragma once
#include <iostream>
#include <fstream>
#include "json\json.h"

class jsonReader
{
public:
	jsonReader();
	jsonReader(std::string jsonFile);
	~jsonReader();

	Json::Value read();

protected:
	void readFromJson(std::string jsonFile);
	Json::Value jsonData;
};

