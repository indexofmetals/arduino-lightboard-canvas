#include "gtest/gtest.h"
#include "Coord.h"

TEST(CoordTest, test1) {
  // make sure the default constructor creates the correct coord
  Coord defaultCoord();
  Coord specificCoord(0, 0);

  EXPECT_EQ(defaultCoord==specificCoord);
}
