#include <gtest/gtest.h>
#include <memory>
#include "../Example.hpp"
//#include "../ECS/Entity.hpp"
#include "../ECS/ComponentManager.hpp"
//#include "../ECS/Entity.hpp"
//#include "../ECS/EntityManager.hpp"


//struct TestComponent{ };
class componentManagerTests : public ::testing::Test {
protected:
	void SetUp() override {
		manager = std::make_unique<ComponentManager<TestComponent>>();
	}

	void TearDown() override
	{
		manager.release();
	}

	Entity e{ 1 };
	TestComponent component{ 0 };
	std::unique_ptr<ComponentManager<TestComponent>> manager;
};

TEST_F(componentManagerTests, AddTwoComponentsIdIncrement) {
	ComponentInstance componentInst = manager->addComponent(e, component);
	ASSERT_EQ(componentInst.instanceId, 1); // stopper ved fejl
	ComponentInstance comp2 = manager->addComponent(e, component);
	ASSERT_EQ(comp2.instanceId, 2);
}

TEST_F(componentManagerTests, NonExistentGetThrow) {
	ASSERT_ANY_THROW(manager->getComponent(e));
}

TEST_F(componentManagerTests, AddGetSame) {
	component.id = 124;
	ComponentInstance componentInst = manager->addComponent(e, component);
	auto cmp = manager->getComponent(e);
	ASSERT_EQ(component.id, cmp->id) << "WHAT";
}
TEST_F(componentManagerTests, RemoveComponent) {
	manager->addComponent(e, component);
	auto cmp = manager->getComponent(e);
	ASSERT_EQ(0, cmp->id);
	manager->removeComponent(e);
	EXPECT_ANY_THROW(manager->getComponent(e));
}
TEST_F(componentManagerTests, RemoveAddAllwaysWitinSize) {
	ComponentInstance inst1 = manager->addComponent(e, component);
	EXPECT_EQ(1, inst1.instanceId);
	Entity e2{ 2 };
	Entity e3{ 3 };
	TestComponent TC2 { 2 };
	TestComponent TC3 { 3 };
	ComponentInstance inst2 = manager->addComponent(e2, TC2);
	EXPECT_EQ(2, inst2.instanceId);
	ComponentInstance inst3 = manager->addComponent(e3, TC3);
	EXPECT_EQ(3, inst3.instanceId);
	manager->removeComponent(e2);
	manager->removeComponent(e3);
	ComponentInstance inst4 = manager->addComponent(e3, TC2);
	ASSERT_EQ(2, inst4.instanceId);
}

class maptest : public ::testing::Test {
protected:
	void SetUp() override {

	}

	Entity e{ 0 };
	EntityMap map;
	ComponentInstance inst{ 1023 };
};
TEST_F(maptest, EntityMapBadGetIdUndefined) {
	Entity x = map.getEntity(inst);
	ASSERT_NE(inst.instanceId, x.id);
}
TEST_F(maptest, EntityMapThrowOnBadGetInst) {
	ASSERT_ANY_THROW(map.getInstance(e));
}
TEST_F(maptest, EntityMapAddInst) {
	map.add(e, inst);
	ASSERT_EQ(map.getEntity(inst).id, e.id);
	ASSERT_EQ(map.getInstance(e).instanceId, inst.instanceId);
}
TEST_F(maptest, EntityMapUpda) {
	map.add(e, inst);
	EXPECT_EQ(map.getEntity(inst).id, e.id);
	EXPECT_EQ(map.getInstance(e).instanceId, inst.instanceId);
	ComponentInstance newInst{ 2 };
	map.update(e, newInst);
	EXPECT_NE(map.getInstance(e).instanceId, inst.instanceId);
	EXPECT_EQ(map.getInstance(e).instanceId, newInst.instanceId);
}
TEST_F(maptest, EntityMapRemove) {
	map.add(e, inst);
	EXPECT_EQ(map.getEntity(inst).id, e.id);
	map.remove(e);
	EXPECT_ANY_THROW(map.getInstance(e));
}
