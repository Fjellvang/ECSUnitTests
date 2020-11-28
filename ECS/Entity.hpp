#pragma once
#include <unordered_map>

struct Entity
{
	unsigned int id;
	//Required for unorderedMap
	bool operator==(const Entity& other) const;
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
