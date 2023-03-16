#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "index.h"
#include <optional>
#include <vector>

template <typename T>
class Gameboard
{
  public:
    /// @invariant @p rows and @p columns must be >= 0.
    Gameboard(const int rows, const int columns);

    int getRows() const;
    int getColumns() const;

    /// @invariant row and column of @p index must be >= 0 and <= number of rows
    /// and columns of this Gameboard.
    void addItem(const T &item, const Index &index);

    /// @invariant row and column of @p index must be >= 0 and <= number of rows
    /// and columns of this Gameboard.
    /// @return true if the operation was successful, or false if there is no
    /// item at the specified @p index.
    bool removeItem(const Index &index);

    /// @invariant row and column of @p index must be >= 0 and <= number of rows
    /// and columns of this Gameboard.
    bool hasItemAt(const Index &index) const;

    /// @pre make sure there is an item at the given @p index.
    /// @invariant row and column of @p index must be >= 0 and <= number of rows
    /// and columns of this Gameboard.
    T &getItem(const Index &index);

    /// @pre make sure there is an item at the given @p index.
    /// @invariant row and column of @p index must be >= 0 and <= number of rows
    /// and columns of this Gameboard.
    const T &getItem(const Index &index) const;

  private:
    int m_rows;
    int m_columns;
    std::vector<std::optional<T>> m_data;
};


#include <cassert>

template <typename T>
Gameboard<T>::Gameboard(const int rows, const int columns) :
  m_rows {rows},
  m_columns {columns},
  m_data(rows * columns, std::nullopt)
{
  assert(rows >= 0 && columns >= 0);
}


template <typename T>
int Gameboard<T>::getRows() const
{
  return m_rows;
}


template <typename T>
int Gameboard<T>::getColumns() const
{
  return m_columns;
}


template <typename T>
void Gameboard<T>::addItem(const T &item, const Index &index)
{
  const int row = index.getRow();
  const int column = index.getColumn();
  assert(row >= 0 && row < m_rows && column >= 0 && column < m_columns);
  m_data[row * m_columns + column] = item;
}


template <typename T>
bool Gameboard<T>::removeItem(const Index &index)
{
  if (hasItemAt(index)) {
    const int row = index.getRow();
    const int column = index.getColumn();
    m_data[row * m_columns + column].reset();
    return true;
  } else {
    return false;
  }
}


template <typename T>
bool Gameboard<T>::hasItemAt(const Index &index) const
{
  const int row = index.getRow();
  const int column = index.getColumn();
  assert(row >= 0 && row < m_rows && column >= 0 && column < m_columns);
  return m_data[row * m_columns + column].has_value();
}


template <typename T>
T &Gameboard<T>::getItem(const Index &index)
{
  const int row = index.getRow();
  const int column = index.getColumn();
  assert(row >= 0 && row < m_rows && column >= 0 && column < m_columns);
  return m_data[row * m_columns + column].value();
}


template <typename T>
const T &Gameboard<T>::getItem(const Index &index) const
{
  const int row = index.getRow();
  const int column = index.getColumn();
  assert(row >= 0 && row < m_rows && column >= 0 && column < m_columns);
  return m_data[row * m_columns + column].value();
}

#endif
