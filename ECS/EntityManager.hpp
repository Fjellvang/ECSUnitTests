#pragma once	
#include "Entity.hpp"

class EntityManager {

public:
	Entity CreateEntity() {
		static unsigned int id = 0;

		Entity e{ id };
		id++;
		return e;
	}
};