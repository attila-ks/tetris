#ifndef TETROMINO_H
#define TETROMINO_H

#include "block.h"
#include "tetrisboard.h"
#include <QObject>

class Tetromino : public QObject
{
    Q_OBJECT

  public:
    enum class Type { I, J, L, O, S, T, Z };

    Tetromino() = default;
    Tetromino(const Type type, const QColor &color, const Index &begin);

    void drawOn(TetrisBoard &tetrisBoard) const;

    void moveDown(TetrisBoard &tetrisBoard);
    void moveLeft(TetrisBoard &tetrisBoard);

  signals:
    void landed();

  private:
    void initBlocks(const QColor &color);

    bool isLegalMove(const TetrisBoard &tetrisBoard) const;

    void removeFrom(TetrisBoard &tetrisBoard);

    void markAsLanded(TetrisBoard &tetrisBoard);

  private:
    Type m_type;
    Index m_begin;
    std::vector<Block> m_blocks;
    std::vector<Block> m_previousStateOfBlocks;
};

#endif
