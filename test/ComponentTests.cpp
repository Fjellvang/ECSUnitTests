#include <gtest/gtest.h>
#include <memory>
#include "../Example.hpp"
#include "../ECS/World.hpp"

class componentBaseTests : public ::testing::Test {
protected:
	void SetUp() override {
	}
	void TearDown() override
	{
	}

};

struct ComponentTest : public ComponentBase<ComponentTest> {};
struct SecondComponentTest : public ComponentBase<SecondComponentTest> {};
struct TransformComponent : public ComponentBase<TransformComponent> {
	TransformComponent(int x) : x(x) {};
	int x;
};

TEST_F(componentBaseTests, componentStartsAtZero) {
	ComponentTest c;
	ASSERT_EQ(0, c.familyId());
}
TEST_F(componentBaseTests, componentFamilyIncrements) {
	ComponentTest c;
	SecondComponentTest c2;
	ASSERT_EQ(c.familyId() + 1, c2.familyId());
}
TEST_F(componentBaseTests, componentStartsAtZeroTemplate) {
	ASSERT_EQ(0, GetComponentFamily<ComponentTest>());
}
TEST_F(componentBaseTests, componentFamilyIncrementsTemplate) {
	ASSERT_EQ(GetComponentFamily<ComponentTest>() + 1, GetComponentFamily<SecondComponentTest>());
}

class worldTests : public ::testing::Test {
protected:
	void SetUp() override {
		world = std::make_unique<World>();
	}
	void TearDown() override
	{
		world.release();
	}


	std::unique_ptr<World> world;
};


TEST_F(worldTests, addComponentNoThrow) {
	Entity e{ 0 };
	ASSERT_NO_THROW(world->addComponent(e, ComponentTest()));
}
TEST_F(worldTests, addComponentGetComponent) {
	Entity e{ 0 };
	TransformComponent comp { 2 };
	ASSERT_NO_THROW(world->addComponent(e, TransformComponent{ 2 }));

	TransformComponent comp2 = * (world->getComponent<TransformComponent>(e));

	ASSERT_EQ(comp.x, comp2.x);
	//ASSERT_EQ(comp.y, comp2.y);
	//ASSERT_EQ(comp.z, comp2.z);
}

