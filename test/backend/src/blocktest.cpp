// TODO: Try to simplify the include paths!
#include "../../../backend/headers/block.h"
#include "../../build/_deps/googletest-src/googletest/include/gtest/gtest.h"

static const QColor color {0xffffff};


TEST(BlockTest, ConstructorWithValidParams)
{
  const Index index {0, 0};
  const Block block {color, index};

  EXPECT_EQ(block.getColor(), color);
  EXPECT_EQ(block.getIndex(), index);
  EXPECT_FALSE(block.isLanded());
}


TEST(BlockTest, ConstructorWithInvalidRowsParam)
{
  const Index index {-1, 0};
  EXPECT_DEATH(Block(color, index), "Assertion");
}


TEST(BlockTest, ConstructorWithInvalidColumnsParam)
{
  const Index index {0, -1};
  EXPECT_DEATH(Block(color, index), "Assertion");
}


TEST(BlockTest, landed)
{
  const Index index {0, 0};
  Block block {color, index};

  block.landed(false);
  EXPECT_FALSE(block.isLanded());
  block.landed(true);
  EXPECT_TRUE(block.isLanded());
}


TEST(BlockTest, setIndexWithValidParam)
{
  const Index index {0, 0};
  Block block {color, index};

  const Index newIndex {5, 5};
  block.setIndex(newIndex);
  EXPECT_EQ(block.getIndex(), newIndex);
}


TEST(BlockTest, setIndexWithInvalidParam)
{
  const Index index {0, 0};
  Block block {color, index};

  EXPECT_DEATH(block.setIndex(Index {-1, 5}), "Assertion");
  EXPECT_DEATH(block.setIndex(Index {5, -1}), "Assertion");
  EXPECT_DEATH(block.setIndex(Index {-1, -1}), "Assertion");
}
