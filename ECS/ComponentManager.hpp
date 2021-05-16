#pragma once
#include "EntityMap.hpp"
#include "ComponentData.hpp"

class BaseComponentManager {
public:
	BaseComponentManager() = default;
	virtual ~BaseComponentManager() = default;
	BaseComponentManager(const BaseComponentManager&) = default;
	BaseComponentManager& operator=(const BaseComponentManager&) = default;
	BaseComponentManager(BaseComponentManager&&) = default;
	BaseComponentManager& operator=(BaseComponentManager&&) = default;
};

template <typename TComponent>
class ComponentManager : public BaseComponentManager {
public:
	//ComponentManager(){}
	ComponentManager() {
		componentData.data = static_cast<std::array<TComponent, MAX_NUMBER_OF_COMPONENTS> *>(malloc(sizeof(TComponent) * 1024));
	}
	//TODO: Consider this. I mean only required once we have more worlds or we can end a managers life..
	//~ComponentManager() {
	//	free(componentData.data);
	//}

	//ComponentManager()
	ComponentInstance addComponent(Entity e, TComponent c) {
		ComponentInstance inst{ componentData.size };
		componentData.data->at(componentData.size) = c;
		componentData.size++;
		entityMap.add(e, inst);
		return inst;
	}

	TComponent * getComponent(Entity e) const {
		ComponentInstance inst = entityMap.getInstance(e);
		unsigned int index = inst.instanceId;
		return &componentData.data->at(index);
	}

	void removeComponent(Entity e) {
		unsigned int index = entityMap.getInstance(e).instanceId;
		unsigned int lastIndex = componentData.size-1;
		componentData.size--;
		entityMap.remove(e);
		if (lastIndex == 1 || lastIndex == index)
		{
			return;
		}
		TComponent cmp = componentData.data->at(lastIndex);
		componentData.data->at(index) = cmp;
		// Now i need cmp to entity, to reshuffle.
		ComponentInstance inst{ lastIndex };
		Entity entity = entityMap.getEntity(inst);
		inst.instanceId = index;
		entityMap.update(entity, inst);
	}


private:
	EntityMap entityMap;
	//std::unordered_map<Entity, ComponentInstance> entityMap; // map from entity to position in array.
	ComponentData<TComponent> componentData;
};
