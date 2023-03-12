#include "../headers/index.h"

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


Index operator+(const Index& lhs, const Index& rhs)
{
  const Index index {lhs.m_row + rhs.m_row, lhs.m_column + rhs.m_column};
  return index;
}


bool operator==(const Index& lhs, const Index& rhs)
{
  return lhs.m_row == rhs.m_row && lhs.m_column == rhs.m_column;
}
