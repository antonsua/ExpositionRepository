#include "Component.h"
#include "Container.h"
#include "Messages_decl.h"

std::vector<std::string> Component::GetWords(std::string& s)
{
	std::vector<std::string> words;
	std::string word;
	for (auto x : s)
	{
		if (x == '/')
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

bool Component::getName(std::string name)
{
	return _name == name;
}

// Update
bool Component::hasUpdate() {
	return uc;
}

void Component::setUpdate() {
	uc = true;
}
