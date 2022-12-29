#ifndef TETROMINO_H
#define TETROMINO_H

#include "block.h"
#include "playfield.h"

class Tetromino
{
  public:
    enum class Type {I, J, L, O, S, T, Z};

    Tetromino(const Type type, const QColor& color, const Position& position);

    void drawOn(Playfield& playfield) const;

  private:
    void initBlocks(const QColor& color);

  private:
    Type m_type;
    Position m_position;
    std::vector<Block> m_blocks;
};

#endif
