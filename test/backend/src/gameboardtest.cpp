// TODO: Try to simplify the include paths!
#include "../../../backend/headers/gameboard.h"
#include "../../build/_deps/googletest-src/googletest/include/gtest/gtest.h"
#include <vector>

using namespace std;

static const int rows = 22;
static const int columns = 10;


TEST(GameboardTest, ConstructorWithValidParams)
{
  Gameboard<int> gameboard {rows, columns};

  EXPECT_EQ(gameboard.getRows(), rows);
  EXPECT_EQ(gameboard.getColumns(), columns);

  for (int row = 0; row < rows; ++row) {
    for (int column = 0; column < columns; ++column) {
      EXPECT_FALSE(gameboard.hasItemAt({row, column}));
    }
  }
}


TEST(GameboardTest, ConstructorWithInvalidParams)
{
  EXPECT_DEATH(Gameboard<int>(-1, -1), "Assertion");
}


TEST(GameBoardTest, addItem)
{
  Gameboard<int> gameboard {rows, columns};

  const int expectedItem = 5;
  const vector<Index> expectedIndexes {{0, 4}, {0, 5}, {1, 3}, {1, 4}};
  for (const Index &index : expectedIndexes) {
    gameboard.addItem(expectedItem, index);
  }

  int foundIndexCounter = 0;
  for (int row = 0; row < rows; ++row) {
    for (int column = 0; column < columns; ++column) {
      const Index actualIndex {row, column};
      if (gameboard.hasItemAt(actualIndex)) {
        const int &actualItem = gameboard.getItem(actualIndex);
        EXPECT_EQ(actualItem, expectedItem);
        EXPECT_EQ(actualIndex, expectedIndexes[foundIndexCounter++]);
      }
    }
  }

  EXPECT_EQ(foundIndexCounter, expectedIndexes.size());
}


TEST(GameboardTest, refdf)
{
  const int item = 5;
  Gameboard<int> gameboard {rows, columns};
  EXPECT_DEATH(gameboard.addItem(item, {-10, -12}), "Assertion");
}


TEST(GameBoardTest, removeItem)
{
  Gameboard<int> gameboard {rows, columns};

  const int item = 5;
  const vector<Index> indexes {{0, 0}, {0, 9}, {21, 0}, {21, 9}};
  for (const Index &index : indexes) {
    gameboard.addItem(item, index);
  }

  for (const Index &index : indexes) {
    EXPECT_TRUE(gameboard.removeItem(index));
  }

  for (int row = 0; row < rows; ++row) {
    for (int column = 0; column < columns; ++column) {
      EXPECT_FALSE(gameboard.hasItemAt({row, column}));
    }
  }
}


TEST(GameBoardTest, removeItemWithWrongIndexParam)
{
  Gameboard<int> gameboard {rows, columns};
  EXPECT_FALSE(gameboard.removeItem({0, 0}));
}
