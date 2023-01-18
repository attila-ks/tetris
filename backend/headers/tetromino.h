#ifndef TETROMINO_H
#define TETROMINO_H

#include "block.h"
#include "playfield.h"
#include <QObject>

class Tetromino : public QObject
{
    Q_OBJECT

  public:
    enum class Type {I, J, L, O, S, T, Z};

    Tetromino();
    Tetromino(const Type type, const QColor& color, const Position& position);

    void drawOn(Playfield& playfield) const;

    void moveDown(Playfield& playfield);

  signals:
    void landed();

  private:
    void initBlocks(const QColor& color);

    bool isLegalMove(const Playfield& playfield) const;

    void removeFrom(Playfield& playfield);

    void markAsLanded(Playfield& playfield);

  private:
    Type m_type;
    Position m_position;
    std::vector<Block> m_blocks;
    std::vector<Block> m_previousStateOfBlocks;
};

#endif
