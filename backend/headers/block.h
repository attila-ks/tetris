#ifndef BLOCK_H
#define BLOCK_H

#include "position.h"
#include <QColor>

class Block
{
  public:
    Block(const QColor& color, const Position& position);

    QColor getColor() const;

    Position getPosition() const;

  private:
    QColor m_color;
    Position m_position;
};

#endif
