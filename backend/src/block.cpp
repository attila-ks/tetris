#include "../headers/block.h"

Block::Block(const QColor& color, const Position& position) :
  m_type {Type::NotLanded},
  m_color {color},
  m_position {position}
{
}


void Block::setType(const Type type)
{
  m_type = type;
}


Block::Type Block::getType() const
{
  return m_type;
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
