#ifndef GHOST_TETROMINO_H
#define GHOST_TETROMINO_H

#include "tetromino.h"

class Playfield;

class GhostTetromino : private Tetromino
{
  public:
    GhostTetromino(const Tetromino &tetrominoToFollow, const QColor &fillColor);

    void drawOn(Playfield &playfield);

    void move(Playfield &playfield);

    void removeFrom(Playfield &playfield);

  private:
    void hardDrop(Playfield &playfield);

    void copyFollowedTetrominoBlockPositions();

    const Tetromino &m_followedTetromino;
};

#endif
