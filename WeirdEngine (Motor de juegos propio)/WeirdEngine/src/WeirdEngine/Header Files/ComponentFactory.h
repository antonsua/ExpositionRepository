#pragma once
#include "C_Factory.h"
#include "FactoriesGestor.h"

#include "Container.h"

#define DEFINE_FACTORY(x) class x##Factory : public CompFactory {\
	public: x##Component* Create(Container* e){\
		return new x##Component(e);}\
	}
#define DEFINE_REGISTER(x) DEFINE_FACTORY(##x); class x##RegisterFact {\
	public: x##RegisterFact(){\
		FactoriesGestor::getInstance()->getFactories().insert({\
			#x, new x##Factory()\
		});\
	}}
#define CREATE_REGISTER(x) DEFINE_REGISTER(##x); x##RegisterFact* x##_aux = new x##RegisterFact(); 