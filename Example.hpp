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
	Entity getEntity(ComponentInstance inst) {
		throw "ERROR";
	}
	ComponentInstance getInstance(Entity e) {
		throw "ERROR";
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
		entityMap[e] = inst;
		return inst;
	}

	TComponent * getComponent(Entity e) const {
		auto it = entityMap.find(e);
		if (it == entityMap.end())
		{
			return nullptr;
		}
		auto index = (it->second).instanceId;
		return &componentData.data->at(index);
	}

	void removeComponent(Entity e) {
		auto it = entityMap.find(e);
		if (it == entityMap.end())
		{
			return;
		}
		auto index = (it->second).instanceId;
		unsigned int lastIndex = componentData.size;
		TComponent cmp = componentData.data->at(lastIndex);

		componentData.data->at(index) = cmp;
		// Now i need cmp to entity, to reshuffle.

	}


private:
	//TODO: Figure out why i cannot used unordered_map??/
	std::unordered_map<Entity, ComponentInstance> entityMap; // map from entity to position in array.
	ComponentData<TComponent> componentData;
};

#endif // !ExampleH
