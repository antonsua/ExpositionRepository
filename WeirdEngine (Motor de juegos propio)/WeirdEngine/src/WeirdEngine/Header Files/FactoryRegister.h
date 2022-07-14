#pragma once
#include <unordered_map>
#include <string>
#include "C_Factory.h"

class FactoryRegister {
public:
	FactoryRegister(std::unordered_map<std::string, CompFactory*>& factories);
};