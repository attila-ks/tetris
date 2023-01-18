#include "../headers/playfield.h"

using namespace std;

QColor Playfield::Cell::m_color;


Playfield::Playfield(const size_t rows, const size_t columns,
                     const QColor& backgroundColor,
                     QAbstractTableModel* parent) :
  QAbstractTableModel {parent},
  m_rows {rows},
  m_columns {columns},
  m_data {rows, vector<Cell> {columns, Cell {}}}
{
  Cell::m_color = backgroundColor;
}


int Playfield::rowCount(const QModelIndex& parent) const
{
  return m_rows;
}


int Playfield::columnCount(const QModelIndex& parent) const
{
  return m_columns;
}


QVariant Playfield::data(const QModelIndex& index, int role) const
{
  const Cell& cell = m_data[index.row()][index.column()];
  if (cell.m_block.has_value())
  {
    return QVariant(cell.m_block.value().getColor());
  }
  else
  {
    return QVariant(Cell::m_color);
  }
}


void Playfield::addBlocks(const vector<Block>& blocks)
{
  for (const Block& block : blocks)
  {
    const Position position = block.getPosition();
    const int row = position.getRow();
    const int column = position.getColumn();
    m_data[row][column].m_block = block;
    auto index = createIndex(row, column);
    emit dataChanged(index, index);
  }
}


bool Playfield::removeBlockAt(const Position& position)
{
  if (hasBlockAt(position))
  {
    const int row = position.getRow();
    const int column = position.getColumn();
    m_data[row][column].m_block.reset();
    auto index = createIndex(row, column);
    emit dataChanged(index, index);
    return true;
  }
  else
  {
    return false;
  }
}


bool Playfield::hasBlockAt(const Position& position) const
{
  const Cell& cell = m_data[position.getRow()][position.getColumn()];
  return cell.m_block.has_value();
}


Block& Playfield::getBlockAt(const Position& position)
{
  return m_data[position.getRow()][position.getColumn()].m_block.value();
}


const Block& Playfield::getConstBlockAt(const Position& position) const
{
  return m_data[position.getRow()][position.getColumn()].m_block.value();
}
