#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <array>
#include <concepts>

template <std::movable T, int ROWS, int COLUMNS>
class Gameboard
{
  public:
    virtual ~Gameboard() = default;

    constexpr int getRows() const;
    constexpr int getColumns() const;

    /// @invariant @p row and @p column must be >= 0 and < than the number of
    /// rows and columns of this Gameboard.
    T &operator()(const int row, const int column);

    /// @invariant @p row and @p column must be >= 0 and < than the number of
    /// rows and columns of this Gameboard.
    const T &operator()(const int row, const int column) const;

    using const_iterator =
        typename std::array<T, ROWS * COLUMNS>::const_iterator;
    using iterator = typename std::array<T, ROWS * COLUMNS>::iterator;
    // The iterator advances row by row.
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    // The iterator advances row by row.
    iterator begin() noexcept;
    iterator end() noexcept;

  private:
    std::array<T, ROWS * COLUMNS> m_data;
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
T &Gameboard<T, ROWS, COLUMNS>::operator()(const int row, const int column)
{
  assert(row >= 0 && row < ROWS && column >= 0 && column < COLUMNS);
  return m_data[row * COLUMNS + column];
}


template <std::movable T, int ROWS, int COLUMNS>
const T &Gameboard<T, ROWS, COLUMNS>::operator()(const int row,
                                                 const int column) const
{
  assert(row >= 0 && row < ROWS && column >= 0 && column < COLUMNS);
  return m_data[row * COLUMNS + column];
}


template <std::movable T, int ROWS, int COLUMNS>
typename Gameboard<T, ROWS, COLUMNS>::const_iterator
Gameboard<T, ROWS, COLUMNS>::begin() const noexcept
{
  return m_data.cbegin();
}


template <std::movable T, int ROWS, int COLUMNS>
typename Gameboard<T, ROWS, COLUMNS>::const_iterator
Gameboard<T, ROWS, COLUMNS>::end() const noexcept
{
  return m_data.cend();
}


template <std::movable T, int ROWS, int COLUMNS>
typename Gameboard<T, ROWS, COLUMNS>::iterator
Gameboard<T, ROWS, COLUMNS>::begin() noexcept
{
  return m_data.begin();
}


template <std::movable T, int ROWS, int COLUMNS>
typename Gameboard<T, ROWS, COLUMNS>::iterator
Gameboard<T, ROWS, COLUMNS>::end() noexcept
{
  return m_data.end();
}

#endif
