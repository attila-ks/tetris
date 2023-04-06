#ifndef TETROMINO_H
#define TETROMINO_H

#include "Playfield.h"
#include "block.h"
#include <QObject>

class Tetromino : public QObject
{
    Q_OBJECT

  public:
    enum class Type { I, J, L, O, S, T, Z };

    Tetromino() = default;
    Tetromino(const Type type, const QColor &color, const Index &begin);

    void drawOn(Playfield &playfield) const;

    void moveDown(Playfield &playfield);
    void moveLeft(Playfield &playfield);
    void moveRight(Playfield &playfield);
    void rotateLeft(Playfield &playfield);
    void rotateRight(Playfield &playfield);
    void hardDrop(Playfield &playfield);

  signals:
    void landed();

  private:
    void initBlocks(const QColor &color);

    bool isLegalMove(const Playfield &playfield) const;

    void removeFrom(Playfield &playfield);

    void markAsLanded(Playfield &playfield);

  private:
    Type m_type;
    Index m_begin;
    std::vector<Block> m_blocks;
    std::vector<Block> m_previousStateOfBlocks;
    int m_rotationIndex;
};

#endif
