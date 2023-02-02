#include "../headers/tetromino.h"
#include <map>

using namespace std;

static const map<Tetromino::Type, vector<vector<Position>>> rotations {
    {Tetromino::Type::I,
     {{Position {1, 0}, Position {1, 1}, Position {1, 2}, Position {1, 3}},
      {Position {0, 2}, Position {1, 2}, Position {2, 2}, Position {3, 2}},
      {Position {2, 0}, Position {2, 1}, Position {2, 2}, Position {2, 3}},
      {Position {0, 1}, Position {1, 1}, Position {2, 1}, Position {3, 1}}}},
    {Tetromino::Type::J,
     {{Position {0, 0}, Position {1, 0}, Position {1, 1}, Position {1, 2}},
      {Position {0, 1}, Position {0, 2}, Position {1, 1}, Position {2, 1}},
      {Position {1, 0}, Position {1, 1}, Position {1, 2}, Position {3, 2}},
      {Position {0, 1}, Position {1, 1}, Position {2, 0}, Position {2, 1}}}},
    {Tetromino::Type::L,
     {{Position {0, 0}, Position {1, 0}, Position {1, 1}, Position {1, 2}},
      {Position {0, 1}, Position {0, 2}, Position {1, 1}, Position {2, 1}},
      {Position {1, 0}, Position {1, 1}, Position {1, 2}, Position {3, 2}},
      {Position {0, 1}, Position {1, 1}, Position {2, 0}, Position {2, 1}}}},
    {Tetromino::Type::O,
     {{Position {0, 0}, Position {0, 1}, Position {1, 0}, Position {1, 1}}}},
    {Tetromino::Type::S,
     {{Position {0, 1}, Position {0, 2}, Position {1, 0}, Position {1, 1}},
      {Position {0, 1}, Position {1, 1}, Position {1, 2}, Position {2, 2}},
      {Position {1, 1}, Position {1, 2}, Position {2, 0}, Position {2, 1}},
      {Position {0, 0}, Position {1, 0}, Position {1, 1}, Position {2, 1}}}},
    {Tetromino::Type::T,
     {{Position {0, 1}, Position {1, 0}, Position {1, 1}, Position {1, 2}},
      {Position {0, 1}, Position {1, 1}, Position {1, 2}, Position {2, 1}},
      {Position {1, 0}, Position {1, 1}, Position {1, 2}, Position {2, 1}},
      {Position {0, 1}, Position {1, 0}, Position {1, 1}, Position {2, 1}}}},
    {Tetromino::Type::Z,
     {{Position {0, 0}, Position {0, 1}, Position {1, 1}, Position {1, 2}},
      {Position {0, 2}, Position {1, 1}, Position {1, 2}, Position {2, 1}},
      {Position {1, 0}, Position {1, 1}, Position {2, 1}, Position {2, 2}},
      {Position {0, 1}, Position {1, 0}, Position {1, 1}, Position {2, 0}}}}};


Tetromino::Tetromino() :
  m_type {},
  m_position {},
  m_blocks {},
  m_previousStateOfBlocks {}
{
}


Tetromino::Tetromino(const Type type, const QColor& color,
                     const Position& position) :
  m_type {type},
  m_position {position},
  m_blocks {},
  m_previousStateOfBlocks {}
{
  initBlocks(color);
}


void Tetromino::drawOn(TetrisBoard& tetrisBoard) const
{
  for (const Block& block : m_blocks)
  {
    tetrisBoard.addBlock(block, block.getPosition());
  }
}


void Tetromino::moveDown(TetrisBoard& tetrisBoard)
{
  m_previousStateOfBlocks = m_blocks;

  for (Block& block : m_blocks)
  {
    Position position = block.getPosition();
    position.setRow(position.getRow() + 1);
    block.setPosition(position);
  }

  if (isLegalMove(tetrisBoard))
  {
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
  for (const Position& blockPosition : rotations.at(m_type)[0])
  {
    m_blocks.push_back(Block {color, blockPosition + m_position});
  }
}


bool Tetromino::isLegalMove(const TetrisBoard& tetrisBoard) const
{
  const int tetrisBoardRowCount = tetrisBoard.rowCount();

  for (const Block& block : m_blocks)
  {
    const Position position = block.getPosition();

    if (position.getRow() == tetrisBoardRowCount)
    {
      return false;
    }
    else if (tetrisBoard.hasBlockAt(position))
    {
      const Block& block = tetrisBoard.getBlock(position);
      if (block.getType() == Block::Type::Landed)
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
    const Position position = block.getPosition();
    tetrisBoard.removeBlock(position);
  }
}


void Tetromino::markAsLanded(TetrisBoard& tetrisBoard)
{
  // This tetromino is going to be destroyed, so only the blocks of tetrisBoard
  // are updated.
  for (Block& block : m_blocks)
  {
    const Position position = block.getPosition();
    tetrisBoard.getBlock(position).setType(Block::Type::Landed);
  }
}
