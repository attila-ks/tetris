#ifndef BLOCK_H
#define BLOCK_H

#include "position.h"
#include <QColor>

class Block
{
  public:
    enum class Type {Landed, NotLanded};

    Block(const QColor& color, const Position& position);

    void setType(const Type type);
    Type getType() const;

    QColor getColor() const;

    void setPosition(const Position& position);
    Position getPosition() const;

  private:
    Type m_type;
    QColor m_color;
    Position m_position;
};

#endif
