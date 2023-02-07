#ifndef POSITION_H
#define POSITION_H

class Position
{
  public:
    Position();
    Position(const int row, const int column);

    void setRow(const int row);
    int getRow() const;

    int getColumn() const;

    Position operator+(const Position& rhs) const;

  private:
    int m_row;
    int m_column;
};

#endif
