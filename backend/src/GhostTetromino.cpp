#include "../headers/GhostTetromino.h"
#include "../headers/Playfield.h"

using namespace std;

GhostTetromino::GhostTetromino(const Tetromino &tetrominoToFollow,
                               const QColor &fillColor) :
  Tetromino {tetrominoToFollow.getType(),
             Block::Type::Ghost,
             fillColor,
             tetrominoToFollow.getBorderColor(),
             tetrominoToFollow.getRow(),
             tetrominoToFollow.getColumn(),
             tetrominoToFollow.getRotationIndex()},
  m_followedTetromino {tetrominoToFollow}
{
}


void GhostTetromino::drawOn(Playfield &playfield)
{
  hardDrop(playfield);

  for (const Block &block : m_blocks) {
    // Prevents removing blocks of the falling Tetromino.
    if (!playfield.hasBlockAt(block.getRow(), block.getColumn())) {
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
  const int bottom = playfield.rowCount();

  for (int i = 1; i < bottom; ++i) {

    m_previousStateOfBlocks = m_blocks;

    for (Block &block : m_blocks) {
      block.setRow(block.getRow() + 1);
    }

    if (!isLegalMove(playfield)) {
      m_blocks = m_previousStateOfBlocks;
      m_row += i;
      removeFrom(playfield);
      break;
    }
  }
}


void GhostTetromino::removeFrom(Playfield &playfield)
{
  for (const Block &block : m_blocks) {
    const int row = block.getRow();
    const int column = block.getColumn();
    if (playfield.hasBlockAt(row, column) &&
        playfield.getBlock(row, column).getType() == Block::Type::Ghost) {
      playfield.removeBlock(row, column);
    }
  }
}


void GhostTetromino::copyFollowedTetrominoBlockPositions()
{
  // TODO: Check whether we need to copy this!
  m_row = m_followedTetromino.getRow();
  m_column = m_followedTetromino.getColumn();

  const vector<Block> &blocks = m_followedTetromino.getBlocks();
  // TODO: Consider to check whether the number of blocks of the two Tetrominoes
  // are equal!
  for (int i = 0; i < blocks.size(); ++i) {
    m_blocks[i].setRow(blocks[i].getRow());
    m_blocks[i].setColumn(blocks[i].getColumn());
  }

  // TODO: Check whether we need to copy this!
  m_rotationIndex = m_followedTetromino.getRotationIndex();
}
