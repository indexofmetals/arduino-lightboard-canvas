#include "unit-tests.h"
#include <src/SubPath.h>

BEGIN_CANVAS_NAMESPACE

END_CANVAS_NAMESPACE

BEGIN_UNNAMED_NAMESPACE

using namespace testing;
using namespace canvas;

TEST(CoordTest, test1) {
  // make sure the default constructor creates the correct coord
  Coord defaultCoord = Coord();
  Coord specificCoord = Coord(0, 0);

  EXPECT_EQ(defaultCoord==specificCoord, 1);
}

END_UNNAMED_NAMESPACE
