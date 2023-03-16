#include "../headers/block.h"

Block::Block(const QColor color, const Index index) :
  m_color {std::move(color)},
  m_index {std::move(index)},
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


const QColor &Block::getColor() const
{
  return m_color;
}


void Block::setIndex(const Index index)
{
  m_index = std::move(index);
}


Index Block::getIndex() const
{
  return m_index;
}
