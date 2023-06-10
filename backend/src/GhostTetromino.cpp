#include "../headers/GhostTetromino.h"
#include "../headers/Playfield.h"

using namespace std;

GhostTetromino::GhostTetromino(const Tetromino &tetrominoToFollow,
                               const QColor &fillColor) :
  Tetromino {tetrominoToFollow.getType(),
             Block::Type::Ghost,
             fillColor,
             tetrominoToFollow.getBorderColor(),
             tetrominoToFollow.getBegin(),
             tetrominoToFollow.getRotationIndex()},
  m_followedTetromino {tetrominoToFollow}
{
}


void GhostTetromino::drawOn(Playfield &playfield)
{
  hardDrop(playfield);

  for (const Block &block : m_blocks) {
    // Prevents removing blocks of the falling Tetromino.
    if (!playfield.hasBlockAt(block.getIndex())) {
      playfield.addBlock(block);
    }
  }
}


void GhostTetromino::move(Playfield &playfield)
{
  removeFrom(playfield);
  copyFollowedTetrominoBlockPositions();
  drawOn(playfield);
}


void GhostTetromino::hardDrop(Playfield &playfield)
{
  const int top = m_begin.getRow();
  const int bottom = playfield.rowCount();

  for (int i = 1; i < bottom; ++i) {

    m_previousStateOfBlocks = m_blocks;

    for (Block &block : m_blocks) {
      const Index &index = block.getIndex();
      block.setIndex(Index {index.getRow() + 1, index.getColumn()});
    }

    if (!isLegalMove(playfield)) {
      m_blocks = m_previousStateOfBlocks;
      m_begin.setRow(m_begin.getRow() + i);
      removeFrom(playfield);
      break;
    }
  }
}


void GhostTetromino::removeFrom(Playfield &playfield)
{
  for (const Block &block : m_blocks) {
    const Index &index = block.getIndex();
    if (playfield.hasBlockAt(index) &&
        playfield.getBlock(index).getType() == Block::Type::Ghost) {
      playfield.removeBlock(index);
    }
  }
}


void GhostTetromino::copyFollowedTetrominoBlockPositions()
{
  // TODO: Check whether we need to copy this!
  m_begin = m_followedTetromino.getBegin();

  const vector<Block> &blocks = m_followedTetromino.getBlocks();
  // TODO: Consider to check whether the number of blocks of the two Tetrominoes
  // are equal!
  for (int i = 0; i < blocks.size(); ++i) {
    m_blocks[i].setIndex(blocks[i].getIndex());
  }

  // TODO: Check whether we need to copy this!
  m_rotationIndex = m_followedTetromino.getRotationIndex();
}
