#ifndef TETROMINO_H
#define TETROMINO_H

#include "block.h"

class Playfield;

class Tetromino
{
  public:
    enum class Type { I, J, L, O, S, T, Z };

    Tetromino() = default;
    Tetromino(const Type type, const QColor &fillColor,
              const QColor &borderColor, const Index &begin);

    Type getType() const;
    const Index &getBegin() const;
    const std::vector<Block> &getBlocks() const;
    const QColor &getBorderColor() const;
    int getRotationIndex() const;
    bool isLanded() const;

    void drawOn(Playfield &playfield) const;

    void moveDown(Playfield &playfield);
    void moveLeft(Playfield &playfield);
    void moveRight(Playfield &playfield);
    void rotateLeft(Playfield &playfield);
    void rotateRight(Playfield &playfield);
    void hardDrop(Playfield &playfield);

    friend std::ofstream &operator<<(std::ofstream &ofstream,
                                     const Tetromino &tetromino);

    friend std::ifstream &operator>>(std::ifstream &ifstream,
                                     Tetromino &tetromino);

  protected:
    Tetromino(const Type type, const Block::Type blockType,
              const QColor &fillColor, const QColor &borderColor,
              const Index &begin, const int rotationIndex = 0);

    bool isLegalMove(const Playfield &playfield) const;

    void removeFrom(Playfield &playfield);

  private:
    void initBlocks(const Block::Type type, const QColor &fillColor,
                    const QColor &borderColor);

    void markAsLanded(Playfield &playfield);

  protected:
    Type m_type;
    Index m_begin;
    std::vector<Block> m_blocks;
    std::vector<Block> m_previousStateOfBlocks;
    int m_rotationIndex;
    bool m_isLanded {false};
};

#endif
