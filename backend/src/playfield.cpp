#include "../headers/playfield.h"

using namespace std;

Playfield::Playfield(const size_t rows, const size_t columns,
                     const QColor& backgroundColor) :
  m_rows {rows},
  m_columns {columns},
  m_backgroundColor {backgroundColor},
  m_data {rows, vector<Cell> {columns, Cell {backgroundColor}}}
{
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
  return QVariant(m_data[index.row()][index.column()].m_color);
}
