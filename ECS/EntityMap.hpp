#pragma once
#include "Entity.hpp"
#include <array>
#include "Statics.hpp"

struct ComponentInstance {
	unsigned int instanceId;
};

class EntityMap {
public:
	Entity getEntity(ComponentInstance inst) const {
		return instanceToEntity.at(inst.instanceId);
	}
	ComponentInstance getInstance(Entity e) const {
		return entityToComponent.at(e);
	}

	void add(Entity e, ComponentInstance inst) {
		entityToComponent.insert({ e, inst });
		instanceToEntity.at(inst.instanceId) = e;
	}
	void update(Entity e, ComponentInstance inst) {
		instanceToEntity.at(inst.instanceId) = e;
		entityToComponent.at(e) = inst;
	}
	// this only removes the entity to instance id.
	// leaving instance to entity, if instance is attempted to be access later it will be undefined...
	void remove(Entity e) {
		entityToComponent.erase(e);
	}
private:
	std::unordered_map<Entity, ComponentInstance> entityToComponent;
	std::array<Entity, MAX_NUMBER_OF_COMPONENTS> instanceToEntity;
};

