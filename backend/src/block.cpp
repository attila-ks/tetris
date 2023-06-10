#include "../headers/block.h"
#include <cstdint>
#include <fstream>
#include <qglobal.h>
#include <qrgb.h>
#include <string>

using namespace std;

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


ostream &operator<<(ostream &ostream, const Block &block)
{
  const Index &index = block.getIndex();
  ostream << static_cast<int>(block.m_type) << ' ' << block.m_fillColor.rgba64()
          << ' ' << block.m_borderColor.rgba64() << ' ' << index.getRow() << ' '
          << index.getColumn();
  return ostream;
}


istream &operator>>(istream &istream, Block &block)
{
  int type;
  quint64 fillColor;
  quint64 borderColor;
  int row;
  int column;
  istream >> type >> fillColor >> borderColor >> row >> column;

  block.m_type = static_cast<Block::Type>(type);
  block.m_fillColor.setRgba64(QRgba64::fromRgba64(fillColor));
  block.m_borderColor.setRgba64(QRgba64::fromRgba64(borderColor));
  block.setIndex(Index {row, column});

  return istream;
}
