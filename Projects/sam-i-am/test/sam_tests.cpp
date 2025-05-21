// tests/sam_unit_tests.cpp
#include <gtest/gtest.h>
#include <vector>
#include "../include/sam_io.h"
#include "../include/sam_types.h"
#include "../include/sam_utils.h"
#include "../include/Game.h"
#include "../include/StaticActor.h"
#include "../include/MovingActor.h"

TEST(Utils, ManhattanDistance) { //simple math
	EXPECT_EQ(SAM::manhattan({ 0, 0 }, { 0, 0 }), 0);
	EXPECT_EQ(SAM::manhattan({ 1, 2 }, { 4, 6 }), 7);
	EXPECT_EQ(SAM::manhattan({ -3, 5 }, { -1, 1 }), 6);
}

TEST(Utils, CoordToStr) {
	EXPECT_EQ(SAM::coordToStr({ 0,0 }), "(1, 1)");
	EXPECT_EQ(SAM::coordToStr({ 4,9 }), "(5, 10)");
}

class GameFixture : public ::testing::Test {
protected:
	SAM::Game g;
	GameFixture() {
		g.makeAndPlaceBattery({ 0, 0 });
	}
};

TEST_F(GameFixture, BoundsChecking) {
	EXPECT_TRUE(g.inBounds({ 0, 0 }));
	EXPECT_TRUE(g.inBounds({ SAM::MAX_X - 1, SAM::MAX_Y - 1 }));
	EXPECT_FALSE(g.inBounds({ -1, 0 }));
	EXPECT_FALSE(g.inBounds({ SAM::MAX_X, 0 }));
	EXPECT_FALSE(g.inBounds({ 0, SAM::MAX_Y }));
}

TEST_F(GameFixture, MakeAndPlaceOverwrite) {
	EXPECT_FALSE(g.makeAndPlaceCity({ 0, 0 })); //should be unable to overwrite
	EXPECT_EQ(g.getCell({ 0,0 })->getMapIcon(), 'B'); //should match original
}

TEST_F(GameFixture, MissileLaunch) {
	g.makeAndPlaceCity({ 2, 2 });
	g.makeAndPlaceMoving(Enemy, SAM::getArchetype(Enemy, 0), North, { 4, 4 }); //within range
	EXPECT_TRUE(g.launchMissile({ 4, 4 })); //should hit, in range
	g.makeAndPlaceMoving(Enemy, SAM::getArchetype(Enemy, 0), North, { 2, 28 }); //out of range
	EXPECT_FALSE(g.launchMissile({ 2, 22 })); //should miss, out of range
	EXPECT_FALSE(g.launchMissile({ 25, 25 })); //should miss without target
}

TEST_F(GameFixture, ActorLeavesOOB) {
	AircraftParams ap = { "Test", 100 }; //test aircraft that should leave bounds in 1 turn
	g.makeAndPlaceMoving(Enemy, ap, North, { 10, 10 });
	g.moveUnits({ {10, 10} });//should immediately be deleted
	EXPECT_FALSE(g.getCell({ 10, 10 })); //source cell should be empty
}

TEST_F(GameFixture, SortByDistance) {
	Coord a1{ 2, 2 }; //4 away
	Coord a2{ 1, 0 }; //1 away
	Coord a3{ 3, 0 }; //3 away
	g.makeAndPlaceCity(a1);
	g.makeAndPlaceCity(a2);
	g.makeAndPlaceCity(a3);
	std::vector<Coord> vec{ a1, a2, a3 };
	vec = g.sortByDistance(vec, g.getPlayerPos());
	EXPECT_EQ(vec[0].x, a2.x); //hacky solution to no overloaded ==
	EXPECT_EQ(vec[1].x, a3.x);
	EXPECT_EQ(vec[2].x, a1.x);
}

TEST_F(GameFixture, LoadScenarioBadValidator) {
	std::vector<char> badScenario{
		(char)(SAM::SAVE_VERSION + 1), //bad validator
		2, //2 static actors
		0, 0, 0, //player at 0,0
		2, 1, 1, //city at 1, 1
		0, //zero mobile actors
		(char)-SAM::SAVE_VERSION //correct exit validator
	};
	EXPECT_THROW(g.loadScenario(badScenario), std::runtime_error);
}

TEST_F(GameFixture, LoadScenarioNoPlayer) {
	std::vector<char> badScenario{
		(char)SAM::SAVE_VERSION, //good validator
		1, //1 static actor
		2, 0, 0, //city at 0, 0
		0, //zero mobile actors
		(char)-SAM::SAVE_VERSION //good exit validator
	};
	EXPECT_THROW(g.loadScenario(badScenario), std::runtime_error);
}

TEST_F(GameFixture, IdentifyAction) {
	Coord c{ 5, 5 };
	g.makeAndPlaceMoving(Enemy, { "Bogey", 1, true, true }, North, c);
	EXPECT_TRUE(g.identify(c)); //should succeed, bogey is now IDed
	EXPECT_FALSE(g.identify(c)); //should fail, bogey is already IDed
}

TEST(Actor, IdentifiedBool) {
	SAM::MovingActor aircraftHostile(Enemy, SAM::getArchetype(Enemy, 0), Bearing::North); //enemy bomber
	SAM::MovingActor aircraftFriendly(Friendly, SAM::getArchetype(Friendly, 0), Bearing::North); //friendly fighter
	EXPECT_FALSE(aircraftHostile.isIdentified);
	EXPECT_TRUE(aircraftFriendly.isIdentified);
}
