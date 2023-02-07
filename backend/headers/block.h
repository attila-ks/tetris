#ifndef BLOCK_H
#define BLOCK_H

#include "position.h"
#include <QColor>

class Block
{
  public:
    /// @invariant row and column of @p position must be >= 0.
    Block(const QColor& color, const Position& position);

    void landed(const bool value);
    bool isLanded() const;

    QColor getColor() const;

    /// @invariant row and column of @p position must be >= 0.
    void setPosition(const Position& position);
    Position getPosition() const;

  private:
    QColor m_color;
    Position m_position;
    bool m_isLanded;
};

#endif
