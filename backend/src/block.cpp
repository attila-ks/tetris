#include "../headers/block.h"
#include <cstdint>
#include <fstream>
#include <qglobal.h>
#include <qrgb.h>
#include <string>

using namespace std;

Block::Block(const Type type, const QColor fillColor, const QColor borderColor,
             const int row, const int column) :
  m_type {type},
  m_fillColor {std::move(fillColor)},
  m_borderColor {std::move(borderColor)},
  m_row {row},
  m_column {column}
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


void Block::setRow(const int row)
{
  m_row = row;
}


int Block::getRow() const
{
  return m_row;
}


void Block::setColumn(const int column)
{
  m_column = column;
}


int Block::getColumn() const
{
  return m_column;
}


ostream &operator<<(ostream &ostream, const Block &block)
{
  ostream << static_cast<int>(block.m_type) << ' ' << block.m_fillColor.rgba64()
          << ' ' << block.m_borderColor.rgba64() << ' ' << block.getRow() << ' '
          << block.getColumn();
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
  block.setRow(row);
  block.setColumn(column);

  return istream;
}
