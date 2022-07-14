#include "jsonReader.h"

jsonReader::jsonReader()
{
}

jsonReader::jsonReader(std::string jsonFile)
{
	readFromJson(jsonFile);
}

jsonReader::~jsonReader()
{
}

///////////////////////////////////////////////////////////////////////////

Json::Value jsonReader::read()
{
	return jsonData;
}

void jsonReader::readFromJson(std::string jsonFile)
{
	std::ifstream ifs(jsonFile);
	Json::CharReaderBuilder jsonReader;
	std::string errs;

	if (Json::parseFromStream(jsonReader, ifs, &jsonData, &errs)) {
		std::cout << "Parse completed sucessfully in " + jsonFile << std::endl;
	}
	else {
		std::cout << errs << std::endl;
	}
}
