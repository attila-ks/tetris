#ifndef BLOCK_H
#define BLOCK_H

#include "index.h"
#include <QColor>

class Block
{
  public:
    Block(const QColor color, const Index index);

    void landed(const bool value);
    bool isLanded() const;

    const QColor &getColor() const;

    void setIndex(const Index index);
    Index getIndex() const;

  private:
    QColor m_color;
    Index m_index;
    bool m_isLanded;
};

#endif
