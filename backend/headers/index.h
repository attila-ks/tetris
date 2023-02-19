#ifndef INDEX_H
#define INDEX_H

class Index
{
  public:
    Index();
    Index(const int row, const int column);

    void setRow(const int row);
    int getRow() const;

    int getColumn() const;

    Index operator+(const Index& rhs) const;
    friend bool operator==(const Index& lhs, const Index& rhs);

  private:
    int m_row;
    int m_column;
};

#endif
