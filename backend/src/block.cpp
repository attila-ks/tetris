#include "../headers/block.h"
#include <cassert>

Block::Block(const QColor& color, const Position& position) :
  m_color {color},
  m_position {position},
  m_isLanded {false}
{
  assert(position.getRow() >= 0 && position.getColumn() >= 0);
}


void Block::landed(const bool value)
{
  m_isLanded = value;
}


bool Block::isLanded() const
{
  return m_isLanded;
}


QColor Block::getColor() const
{
  return m_color;
}


void Block::setPosition(const Position& position)
{
  assert(position.getRow() >= 0 && position.getColumn() >= 0);
  m_position = position;
}


Position Block::getPosition() const
{
  return m_position;
}
