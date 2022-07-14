#pragma once

#include <unordered_map>
#include <string>

class CompFactory;

class FactoriesGestor {
public:
	
	std::unordered_map<std::string, CompFactory*>& getFactories() { return factories; };
	static FactoriesGestor* getInstance() {
		if (_instance == NULL) { _instance = new FactoriesGestor(); }
		return _instance;
	}
private:
	FactoriesGestor();

	static FactoriesGestor* _instance;

	//Data
	std::unordered_map<std::string, CompFactory*> factories;
};