#include "../headers/block.h"

Block::Block(const Type type, const QColor fillColor, const QColor borderColor,
             const Index index) :
  m_type {type},
  m_fillColor {std::move(fillColor)},
  m_borderColor {std::move(borderColor)},
  m_index {std::move(index)}
{
  // TODO: Consider to add assertion for `index` param.
}


void Block::setType(const Type type)
{
  m_type = type;
}


Block::Type Block::getType() const
{
  return m_type;
}


void Block::setFillColor(const QColor fillColor)
{
  m_fillColor = std::move(fillColor);
}


const QColor &Block::getFillColor() const
{
  return m_fillColor;
}


const QColor &Block::getBorderColor() const
{
  return m_borderColor;
}


void Block::setIndex(const Index index)
{
  m_index = std::move(index);
}


const Index &Block::getIndex() const
{
  return m_index;
}
