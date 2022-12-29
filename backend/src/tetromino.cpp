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


Tetromino::Tetromino(const Type type, const QColor& color,
                     const Position& position) :
  m_type {type},
  m_position {position},
  m_blocks {}
{
  initBlocks(color);
}


void Tetromino::drawOn(Playfield& playfield) const
{
  playfield.addBlocks(m_blocks);
}


void Tetromino::initBlocks(const QColor& color)
{
  for (const Position& blockPosition : rotations.at(m_type)[0])
  {
    m_blocks.push_back(Block {color, blockPosition + m_position});
  }
}
