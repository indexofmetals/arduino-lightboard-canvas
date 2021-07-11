#include "gtest/gtest.h"
#include "SubPath.h"

TEST(CoordTest, test1) {
  // make sure the default constructor creates the correct coord
  Coord defaultCoord = Coord();
  Coord specificCoord = Coord(0, 0);

  EXPECT_EQ(defaultCoord==specificCoord, 1);
}
