#include "TestComponent.h"
#include <iostream>

TestComponent::TestComponent(EntityC* e)
{
	_name = "Test";
}

void TestComponent::Init(std::unordered_map<std::string, std::string>& param)
{
	f = std::stof(param.at("float"));

	std::vector<std::string> words = GetWords(param.at("aint"));

	for (size_t i = 0; i < 3; i++)
	{
		intArray[i] = std::stoi(words[i]);
	}

	s = param.at("string");

	if (param.at("bool") == "true")
		b = true;
	else
		b = false;
}

void TestComponent::Debug()
{
	std::cout << "Float: " << f << '\n';
	std::cout << "String: " << s << '\n';
	std::cout << "Bool: " << b << '\n';
	std::cout << "Int Array: ";
	for (size_t i = 0; i < 3; i++)
	{
		std::cout << intArray[i] << '|';
	}
	std::cout << '\n';
}