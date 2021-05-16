#include <gtest/gtest.h>
#include <memory>
#include "../Example.hpp"
#include "../ECS/Entity.hpp"

class entityManagerTests : public ::testing::Test {
protected:
	void SetUp() override {
		manager = std::make_unique<EntityManager>();
	}
	void TearDown() override
	{
		manager.release();
	}

	std::unique_ptr<EntityManager> manager;
};

TEST_F(entityManagerTests, EntityManagerIdIncrements) {
	Entity e = manager->CreateEntity();
	Entity e2 = manager->CreateEntity();
	ASSERT_EQ(e.id + 1, e2.id);
}
