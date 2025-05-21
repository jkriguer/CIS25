// tests/sam_unit_tests.cpp
#include <gtest/gtest.h>
#include "../include/sam_types.h"
#include "../include/sam_utils.h"
#include "../include/Game.h"
#include "../include/StaticActor.h"
#include "../include/MovingActor.h"

TEST(Utils, manhattanDistance) { //simple math
	EXPECT_EQ(SAM::manhattan({ 0, 0 }, { 0, 0 }), 0);
	EXPECT_EQ(SAM::manhattan({ 1, 2 }, { 4, 6 }), 7);
	EXPECT_EQ(SAM::manhattan({ -3, 5 }, { -1, 1 }), 6);
}

TEST(Utils, coordToStr) {
	EXPECT_EQ(SAM::coordToStr({ 0,0 }), "(1, 1)");
	EXPECT_EQ(SAM::coordToStr({ 4,9 }), "(5, 10)");
}

class GameFixture : public ::testing::Test {
protected:
	SAM::Game g;
	GameFixture() {
		g.makeAndPlace(Player, "Player", 'P', { 0, 0 });
	}
};

TEST_F(GameFixture, boundsChecking) {
	EXPECT_TRUE(g.inBounds({ 0, 0 }));
	EXPECT_TRUE(g.inBounds({ g.DIM_X - 1, g.DIM_Y - 1 }));
	EXPECT_FALSE(g.inBounds({ -1, 0 }));
	EXPECT_FALSE(g.inBounds({ g.DIM_X, 0 }));
	EXPECT_FALSE(g.inBounds({ 0, g.DIM_Y }));
}

TEST_F(GameFixture, makeAndPlaceOverwrite) {
	EXPECT_FALSE(g.makeAndPlace(Player, "Spare", 'S', { 0, 0 })); //should be unable to overwrite
	EXPECT_EQ(g.getCell({ 0,0 })->getMapIcon(), 'P'); //should match original
}

TEST_F(GameFixture, missileLaunch) {
	g.makeAndPlace(City, "City", 'C', { 2, 2 });
	g.makeAndPlace(Enemy, SAM::getArchetype(Enemy, 0), North, { 4, 4 }); //within range
	EXPECT_TRUE(g.launchMissile({ 4, 4 })); //should hit, in range
	g.makeAndPlace(Enemy, SAM::getArchetype(Enemy, 0), North, { 2, 30 }); //out of range
	EXPECT_FALSE(g.launchMissile({ 2, 22 })); //should miss, out of range
	EXPECT_FALSE(g.launchMissile({ 25, 25 })); //should miss without target
}

TEST_F(GameFixture, actorLeavesOOB) {
	g.makeAndPlace(Player, "Test Battery", 'T', { 2, 2 });
	AircraftParams ap = { "Test", 100 }; //test aircraft that should leave bounds in 1 turn
	g.makeAndPlace(Enemy, ap, North, { 10, 10 });
	g.moveUnits({ {10, 10} });//should immediately be deleted
	EXPECT_FALSE(g.getCell({ 10, 10 })); //source cell should be empty
}

TEST_F(GameFixture, sortByDistance) {
	Coord a1{ 2, 2 }; //4 away
	Coord a2{ 1, 0 }; //1 away
	Coord a3{ 3, 0 }; //3 away
	g.makeAndPlace(City, "A1", '1', a1);
	g.makeAndPlace(City, "A2", '2', a2);
	g.makeAndPlace(City, "A3", '3', a3);
	std::vector<Coord> vec{ a1, a2, a3 };
	vec = g.sortByDistance(vec, g.getPlayerPos());
	EXPECT_EQ(vec[0].x, a2.x); //hacky solution to no overloaded ==
	EXPECT_EQ(vec[1].x, a3.x);
	EXPECT_EQ(vec[2].x, a1.x);
}

TEST(Actor, tickID) {
	AircraftParams ap = SAM::getArchetype(Enemy, 0); //enemy bomber
	SAM::MovingActor aircraft(Enemy, ap, Bearing::North);
	EXPECT_EQ(aircraft.getID(), 1);
	EXPECT_TRUE(aircraft.tickID());
	EXPECT_EQ(aircraft.getID(), 0);
	EXPECT_FALSE(aircraft.tickID()); //should not go negative
	EXPECT_EQ(aircraft.getID(), 0);
}

