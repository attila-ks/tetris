#ifndef POSITION_H
#define POSITION_H

class Position
{
  public:
    Position();
    /// @param row must be greater than or equal to 0.
    /// @param column must be greater than or equal to 0.
    Position(const int row, const int column);

    int getRow() const;
    int getColumn() const;

    Position operator+(const Position& rhs) const;

  private:
    int m_row;
    int m_column;
};

#endif
