#include "../headers/index.h"

Index::Index() :
  m_row {},
  m_column {}
{
}


Index::Index(const int row, const int column) :
  m_row {row},
  m_column {column}
{
}


void Index::setRow(const int row)
{
  m_row = row;
}


int Index::getRow() const
{
  return m_row;
}


int Index::getColumn() const
{
  return m_column;
}


Index Index::operator+(const Index& rhs) const
{
  return Index(m_row + rhs.m_row, m_column + rhs.m_column);
}
