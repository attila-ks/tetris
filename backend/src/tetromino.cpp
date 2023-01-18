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


void Tetromino::drawOn(Playfield& playfield) const
{
  playfield.addBlocks(m_blocks);
}


void Tetromino::moveDown(Playfield& playfield)
{
  m_previousStateOfBlocks = m_blocks;

  for (Block& block : m_blocks)
  {
    Position position = block.getPosition();
    position.setRow(position.getRow() + 1);
    block.setPosition(position);
  }

  if (isLegalMove(playfield))
  {
    removeFrom(playfield);
    drawOn(playfield);
  }
  else
  {
    m_blocks = m_previousStateOfBlocks;
  }
}


void Tetromino::initBlocks(const QColor& color)
{
  for (const Position& blockPosition : rotations.at(m_type)[0])
  {
    m_blocks.push_back(Block {color, blockPosition + m_position});
  }
}


bool Tetromino::isLegalMove(const Playfield& playfield) const
{
  for (const Block& block : m_blocks)
  {
    const Position position = block.getPosition();

    if (playfield.hasBlockAt(position))
    {
      const Block& block = playfield.getBlockAt(position);
      if (block.getType() == Block::Type::Landed)
          [[unlikely]] // Does this attribute make sense here?
      {
        return false;
      }
    }
  }

  return true;
}


void Tetromino::removeFrom(Playfield& playfield)
{
  for (const Block& block : m_previousStateOfBlocks)
  {
    const Position position = block.getPosition();
    playfield.removeBlockAt(position);
  }
}
