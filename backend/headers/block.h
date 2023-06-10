#ifndef BLOCK_H
#define BLOCK_H

#include "index.h"
#include <QColor>

class Block
{
  public:
    enum class Type { Falling, Landed, Ghost };

    Block() = default;
    Block(const Type type, const QColor fillColor, const QColor borderColor,
          const Index index);

    void setType(const Type type);
    Type getType() const;

    void setFillColor(const QColor fillColor);
    const QColor &getFillColor() const;

    const QColor &getBorderColor() const;

    void setIndex(const Index index);
    const Index &getIndex() const;

    friend std::ostream &operator<<(std::ostream &ostream, const Block &block);
    friend std::istream &operator>>(std::istream &istream, Block &block);

  private:
    Type m_type;
    QColor m_fillColor;
    QColor m_borderColor;
    Index m_index;
};

#endif
