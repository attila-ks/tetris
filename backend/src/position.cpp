#include "../headers/position.h"
#include <cassert>

Position::Position() :
  m_row {},
  m_column {}
{
}


Position::Position(const int row, const int column) :
  m_row {row},
  m_column {column}
{
  assert(row >= 0 && column >= 0);
}


int Position::getRow() const
{
  return m_row;
}


int Position::getColumn() const
{
  return m_column;
}


Position Position::operator+(const Position& rhs) const
{
  return Position(m_row + rhs.m_row, m_column + rhs.m_column);
}
