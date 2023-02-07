#include "../headers/block.h"

Block::Block(const QColor& color, const Position& position) :
  m_color {color},
  m_position {position},
  m_isLanded {false}
{
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
  m_position = position;
}


Position Block::getPosition() const
{
  return m_position;
}
