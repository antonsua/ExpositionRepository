#include "FactoriesGestor.h"


FactoriesGestor::FactoriesGestor() {
	factories = std::unordered_map < std::string, CompFactory*>();
}

FactoriesGestor* FactoriesGestor::_instance = NULL;