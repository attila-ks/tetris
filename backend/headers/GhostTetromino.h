#ifndef GHOST_TETROMINO_H
#define GHOST_TETROMINO_H

#include "tetromino.h"

class Playfield;

class GhostTetromino : Tetromino
{
  public:
    GhostTetromino(const Tetromino &tetrominoToFollow, const QColor &fillColor);

    void drawOn(Playfield &playfield);

    void move(Playfield &playfield);

  private:
    void hardDrop(Playfield &playfield);
    void removeFrom(Playfield &playfield);

    void copyFollowedTetrominoBlockPositions();

    using Tetromino::getType;
    using Tetromino::getBegin;
    using Tetromino::getBlocks;
    using Tetromino::getBorderColor;
    using Tetromino::getRotationIndex;
    using Tetromino::moveDown;
    using Tetromino::moveLeft;
    using Tetromino::moveRight;
    using Tetromino::rotateLeft;
    using Tetromino::rotateRight;

    const Tetromino &m_followedTetromino;
};

#endif
