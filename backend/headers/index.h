#ifndef INDEX_H
#define INDEX_H

class Index
{
  public:
    Index() = default;
    Index(const int row, const int column);

    void setRow(const int row);
    int getRow() const;

    int getColumn() const;

    friend Index operator+(const Index &lhs, const Index &rhs);
    friend bool operator==(const Index &lhs, const Index &rhs);

  private:
    int m_row;
    int m_column;
};

#endif
