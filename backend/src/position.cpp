#include "../headers/position.h"

Position::Position() :
  m_row {},
  m_column {}
{
}


Position::Position(const int row, const int column) :
  m_row {row},
  m_column {column}
{
}


void Position::setRow(const int row)
{
  m_row = row;
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
