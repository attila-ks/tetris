#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "index.h"
#include <array>
#include <concepts>
#include <optional>

template <std::movable T, int ROWS, int COLUMNS>
class Gameboard
{
  public:
    virtual ~Gameboard() = default;

    constexpr int getRows() const;
    constexpr int getColumns() const;

    /// @invariant row and column of @p index must be >= 0 and <= number of rows
    /// and columns of this Gameboard.
    void addItem(const T item, const Index &index);

    /// @pre make sure there is an item at the given @p index.
    /// @invariant row and column of @p index must be >= 0 and <= number of rows
    /// and columns of this Gameboard.
    /// @return the removed item at the specified @p index.
    T removeItem(const Index &index);

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
    std::array<std::optional<T>, ROWS * COLUMNS> m_data;
};


#include <cassert>

template <std::movable T, int ROWS, int COLUMNS>
constexpr int Gameboard<T, ROWS, COLUMNS>::getRows() const
{
  return ROWS;
}


template <std::movable T, int ROWS, int COLUMNS>
constexpr int Gameboard<T, ROWS, COLUMNS>::getColumns() const
{
  return COLUMNS;
}


template <std::movable T, int ROWS, int COLUMNS>
void Gameboard<T, ROWS, COLUMNS>::addItem(const T item, const Index &index)
{
  const int row = index.getRow();
  const int column = index.getColumn();
  assert(row >= 0 && row < ROWS && column >= 0 && column < COLUMNS);
  m_data[row * COLUMNS + column] = std::move(item);
}


template <std::movable T, int ROWS, int COLUMNS>
T Gameboard<T, ROWS, COLUMNS>::removeItem(const Index &index)
{
  assert(hasItemAt(index));

  const int row = index.getRow();
  const int column = index.getColumn();
  const T &item = m_data[row * COLUMNS + column].value();
  m_data[row * COLUMNS + column] = std::nullopt;
  return item;
}


template <std::movable T, int ROWS, int COLUMNS>
bool Gameboard<T, ROWS, COLUMNS>::hasItemAt(const Index &index) const
{
  const int row = index.getRow();
  const int column = index.getColumn();
  assert(row >= 0 && row < ROWS && column >= 0 && column < COLUMNS);
  return m_data[row * COLUMNS + column].has_value();
}


template <std::movable T, int ROWS, int COLUMNS>
T &Gameboard<T, ROWS, COLUMNS>::getItem(const Index &index)
{
  const int row = index.getRow();
  const int column = index.getColumn();
  assert(row >= 0 && row < ROWS && column >= 0 && column < COLUMNS);
  return m_data[row * COLUMNS + column].value();
}


template <std::movable T, int ROWS, int COLUMNS>
const T &Gameboard<T, ROWS, COLUMNS>::getItem(const Index &index) const
{
  const int row = index.getRow();
  const int column = index.getColumn();
  assert(row >= 0 && row < ROWS && column >= 0 && column < COLUMNS);
  return m_data[row * COLUMNS + column].value();
}

#endif
