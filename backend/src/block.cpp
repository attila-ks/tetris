#include "../headers/block.h"

Block::Block(const QColor& color, const Position& position) :
  m_color {color},
  m_position {position}
{
}


QColor Block::getColor() const
{
  return m_color;
}


Position Block::getPosition() const
{
  return m_position;
}
