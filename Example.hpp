#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP
#include <unordered_map>
#include <map>
#include <array>
#include <memory>

const int MAX_NUMBER_OF_COMPONENTS = 1024;
struct Entity
{
	unsigned int id;
	//Required for unorderedMap
	bool operator==(const Entity& other) const
	{
		return (id == other.id);
	}
};

namespace std {
	//required for unordered_map
	template <>
	struct hash<Entity>
	{
		std::size_t operator()(const Entity& k) const
		{
			using std::size_t;
			using std::hash;
			return ((hash<unsigned int>()(k.id)));
		}
	};
}

struct ComponentBase {
	//Entity * entity; //TODO: not sure we want to keep this. Evauluate
};


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
struct ComponentData {
	unsigned int size{ 1 };// where are we initialized to ... 1 ?
	std::array<TComponent, MAX_NUMBER_OF_COMPONENTS> * data; // pre allocated array of components
};

struct TestComponent {
	int id;
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

#endif // !ExampleH
