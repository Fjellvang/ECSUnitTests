#pragma once
#include <array>
#include "Statics.hpp"


template <typename TComponent>
struct ComponentData {
	unsigned int size{ 1 };// where are we initialized to ... 1 ?
	std::array<TComponent, MAX_NUMBER_OF_COMPONENTS> * data; // pre allocated array of components
};

