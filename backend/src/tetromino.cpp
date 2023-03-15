#include "../headers/tetromino.h"
#include <map>

using namespace std;

static const map<Tetromino::Type, vector<vector<Index>>> rotations {
    {Tetromino::Type::I,
     {{Index {0, 0}, Index {0, 1}, Index {0, 2}, Index {0, 3}},
      {Index {0, 2}, Index {1, 2}, Index {2, 2}, Index {3, 2}},
      {Index {2, 0}, Index {2, 1}, Index {2, 2}, Index {2, 3}},
      {Index {0, 1}, Index {1, 1}, Index {2, 1}, Index {3, 1}}}},
    {Tetromino::Type::J,
     {{Index {0, 0}, Index {1, 0}, Index {1, 1}, Index {1, 2}},
      {Index {0, 1}, Index {0, 2}, Index {1, 1}, Index {2, 1}},
      {Index {1, 0}, Index {1, 1}, Index {1, 2}, Index {3, 2}},
      {Index {0, 1}, Index {1, 1}, Index {2, 0}, Index {2, 1}}}},
    {Tetromino::Type::L,
     {{Index {0, 0}, Index {1, -2}, Index {1, -1}, Index {1, 0}},
      {Index {0, 1}, Index {0, 2}, Index {1, 1}, Index {2, 1}},
      {Index {1, 0}, Index {1, 1}, Index {1, 2}, Index {3, 2}},
      {Index {0, 1}, Index {1, 1}, Index {2, 0}, Index {2, 1}}}},
    {Tetromino::Type::O,
     {{Index {0, 0}, Index {0, 1}, Index {1, 0}, Index {1, 1}}}},
    {Tetromino::Type::S,
     {{Index {0, 0}, Index {0, 1}, Index {1, -1}, Index {1, 0}},
      {Index {0, 1}, Index {1, 1}, Index {1, 2}, Index {2, 2}},
      {Index {1, 1}, Index {1, 2}, Index {2, 0}, Index {2, 1}},
      {Index {0, 0}, Index {1, 0}, Index {1, 1}, Index {2, 1}}}},
    {Tetromino::Type::T,
     {{Index {0, 0}, Index {1, -1}, Index {1, 0}, Index {1, 1}},
      {Index {0, 1}, Index {1, 1}, Index {1, 2}, Index {2, 1}},
      {Index {1, 0}, Index {1, 1}, Index {1, 2}, Index {2, 1}},
      {Index {0, 1}, Index {1, 0}, Index {1, 1}, Index {2, 1}}}},
    {Tetromino::Type::Z,
     {{Index {0, 0}, Index {0, 1}, Index {1, 1}, Index {1, 2}},
      {Index {0, 2}, Index {1, 1}, Index {1, 2}, Index {2, 1}},
      {Index {1, 0}, Index {1, 1}, Index {2, 1}, Index {2, 2}},
      {Index {0, 1}, Index {1, 0}, Index {1, 1}, Index {2, 0}}}}};


Tetromino::Tetromino(const Type type, const QColor& color,
                     const Index& begin) :
  m_type {type},
  m_begin {begin},
  m_blocks {},
  m_previousStateOfBlocks {}
{
  initBlocks(color);
}


void Tetromino::drawOn(TetrisBoard& tetrisBoard) const
{
  for (const Block& block : m_blocks)
  {
    tetrisBoard.addBlock(block);
  }
}


void Tetromino::moveDown(TetrisBoard& tetrisBoard)
{
  m_previousStateOfBlocks = m_blocks;

  for (Block& block : m_blocks)
  {
    Index index = block.getIndex();
    index.setRow(index.getRow() + 1);
    block.setIndex(index);
  }

  if (isLegalMove(tetrisBoard))
  {
    m_begin.setRow(m_begin.getRow() + 1);
    removeFrom(tetrisBoard);
    drawOn(tetrisBoard);
  }
  else
  {
    m_blocks = m_previousStateOfBlocks;
    markAsLanded(tetrisBoard);
    emit landed();
  }
}


void Tetromino::initBlocks(const QColor& color)
{
  for (const Index& blockIndex : rotations.at(m_type)[0])
  {
    m_blocks.push_back(Block {color, blockIndex + m_begin});
  }
}


bool Tetromino::isLegalMove(const TetrisBoard& tetrisBoard) const
{
  const int tetrisBoardRowCount = tetrisBoard.rowCount();

  for (const Block& block : m_blocks)
  {
    const Index index = block.getIndex();

    if (index.getRow() == tetrisBoardRowCount)
    {
      return false;
    }
    else if (tetrisBoard.hasBlockAt(index))
    {
      const Block& block = tetrisBoard.getBlock(index);
      if (block.isLanded())
      {
        return false;
      }
    }
  }

  return true;
}


void Tetromino::removeFrom(TetrisBoard& tetrisBoard)
{
  for (const Block& block : m_previousStateOfBlocks)
  {
    const Index index = block.getIndex();
    tetrisBoard.removeBlock(index);
  }
}


void Tetromino::markAsLanded(TetrisBoard& tetrisBoard)
{
  // This tetromino is going to be destroyed, so only the blocks of tetrisBoard
  // are updated.
  for (Block& block : m_blocks)
  {
    const Index index = block.getIndex();
    tetrisBoard.getBlock(index).landed(true);
  }
}
