// tests/sam_unit_tests.cpp
#include <gtest/gtest.h>
#include "../include/sam_types.h"
#include "../include/sam_utils.h"
#include "../include/Game.h"
#include "../include/Actor.h"

TEST(Utils, manhattanDistance) { //simple math
    EXPECT_EQ(SAM::manhattan({ 0,0 }, { 0,0 }), 0);
    EXPECT_EQ(SAM::manhattan({ 1,2 }, { 4,6 }), 7);
    EXPECT_EQ(SAM::manhattan({ -3,5 }, { -1,1 }), 6);
}

TEST(Utils, coordToStr) {
    EXPECT_EQ(SAM::coordToStr({ 0,0 }), "(1, 1)");
    EXPECT_EQ(SAM::coordToStr({ 4,9 }), "(5, 10)");
}

class Fixture : public ::testing::Test {
protected:
    SAM::Game g;
};

TEST_F(Fixture, boundsChecking) {
    EXPECT_TRUE(g.inBounds(0, 0));
    EXPECT_TRUE(g.inBounds(g.getWidth() - 1, g.getHeight() - 1));
    EXPECT_FALSE(g.inBounds(-1, 0));
    EXPECT_FALSE(g.inBounds(g.getWidth(), 0));
    EXPECT_FALSE(g.inBounds(0, g.getHeight()));
}

TEST_F(Fixture, makeAndPlaceOverwrite) {
    bool actor1 = g.makeAndPlace(Player, "Battery", 'B', 5, 5); //should succeed
    bool actor2 = g.makeAndPlace(Player, "Spare", 'S', 5, 5); //should fail
    auto& cell = g.getCell(5, 5);
    ASSERT_TRUE(cell);
    EXPECT_EQ(cell->getMapIcon(), 'B');
    EXPECT_TRUE(actor1);
    EXPECT_FALSE(actor2);
}

TEST(Actor, tickID) {
    AircraftParams ap = SAM::getArchetype(Enemy, 0); //enemy bomber
    Actor aircraft(Enemy, ap, Bearing::North);
    EXPECT_EQ(aircraft.getID(), 2);
    EXPECT_TRUE(aircraft.tickID());
    EXPECT_EQ(aircraft.getID(), 1);
    EXPECT_TRUE(aircraft.tickID());
    EXPECT_EQ(aircraft.getID(), 0);
    EXPECT_FALSE(aircraft.tickID()); //should not go negative
    EXPECT_EQ(aircraft.getID(), 0);
}

TEST(Actor, sortByDistance) {
    SharedActor a1 = std::make_shared<Actor>(City, "A1", '1');
    SharedActor a2 = std::make_shared<Actor>(City, "A2", '2');
    SharedActor a3 = std::make_shared<Actor>(City, "A3", '3');
    Coord player(0, 0);
    a1->setActorCoords(Coord(2, 2)); //4
    a2->setActorCoords(Coord(1, 0)); //1
    a3->setActorCoords(Coord(3, 0)); //3
    std::vector<SharedActor> vec{ a1, a2, a3 };
    SAM::sortContactsByDistance(vec, player);
    EXPECT_EQ(vec[0], a2);
    EXPECT_EQ(vec[1], a3);
    EXPECT_EQ(vec[2], a1);
}