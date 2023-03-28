#include "../headers/tetromino.h"
#include <map>

using namespace std;

static const map<Tetromino::Type, vector<vector<Index>>> rotations {
    {Tetromino::Type::I,
     {{Index {0, 0}, Index {0, 1}, Index {0, 2}, Index {0, 3}},
      {Index {-1, 2}, Index {0, 2}, Index {1, 2}, Index {2, 2}},
      {Index {1, 0}, Index {1, 1}, Index {1, 2}, Index {1, 3}},
      {Index {-1, 1}, Index {0, 1}, Index {1, 1}, Index {2, 1}}}},
    {Tetromino::Type::J,
     {{Index {0, 0}, Index {1, 0}, Index {1, 1}, Index {1, 2}},
      {Index {0, 1}, Index {0, 2}, Index {1, 1}, Index {2, 1}},
      {Index {1, 0}, Index {1, 1}, Index {1, 2}, Index {2, 2}},
      {Index {0, 1}, Index {1, 1}, Index {2, 0}, Index {2, 1}}}},
    {Tetromino::Type::L,
     {{Index {0, 2}, Index {1, 0}, Index {1, 1}, Index {1, 2}},
      {Index {0, 1}, Index {1, 1}, Index {2, 1}, Index {2, 2}},
      {Index {1, 0}, Index {1, 1}, Index {1, 2}, Index {2, 0}},
      {Index {0, 0}, Index {0, 1}, Index {1, 1}, Index {2, 1}}}},
    {Tetromino::Type::O,
     {{Index {0, 0}, Index {0, 1}, Index {1, 0}, Index {1, 1}}}},
    {Tetromino::Type::S,
     {{Index {0, 1}, Index {0, 2}, Index {1, 0}, Index {1, 1}},
      {Index {0, 1}, Index {1, 1}, Index {1, 2}, Index {2, 2}},
      {Index {1, 1}, Index {1, 2}, Index {2, 0}, Index {2, 1}},
      {Index {0, 0}, Index {1, 0}, Index {1, 1}, Index {2, 1}}}},
    {Tetromino::Type::T,
     {{Index {0, 1}, Index {1, 0}, Index {1, 1}, Index {1, 2}},
      {Index {0, 1}, Index {1, 1}, Index {1, 2}, Index {2, 1}},
      {Index {1, 0}, Index {1, 1}, Index {1, 2}, Index {2, 1}},
      {Index {0, 1}, Index {1, 0}, Index {1, 1}, Index {2, 1}}}},
    {Tetromino::Type::Z,
     {{Index {0, 0}, Index {0, 1}, Index {1, 1}, Index {1, 2}},
      {Index {0, 2}, Index {1, 1}, Index {1, 2}, Index {2, 1}},
      {Index {1, 0}, Index {1, 1}, Index {2, 1}, Index {2, 2}},
      {Index {0, 1}, Index {1, 0}, Index {1, 1}, Index {2, 0}}}}};


Tetromino::Tetromino(const Type type, const QColor &color, const Index &begin) :
  m_type {type},
  m_begin {begin},
  m_blocks {},
  m_previousStateOfBlocks {},
  m_rotationIndex {0}
{
  initBlocks(color);
}


void Tetromino::drawOn(TetrisBoard &tetrisBoard) const
{
  for (const Block &block : m_blocks) {
    tetrisBoard.addBlock(block);
  }
}


void Tetromino::moveDown(TetrisBoard &tetrisBoard)
{
  m_previousStateOfBlocks = m_blocks;

  for (Block &block : m_blocks) {
    Index index = block.getIndex();
    index.setRow(index.getRow() + 1);
    block.setIndex(index);
  }

  if (isLegalMove(tetrisBoard)) {
    m_begin.setRow(m_begin.getRow() + 1);
    removeFrom(tetrisBoard);
    drawOn(tetrisBoard);
  } else {
    m_blocks = m_previousStateOfBlocks;
    markAsLanded(tetrisBoard);
    emit landed();
  }
}


void Tetromino::moveLeft(TetrisBoard &tetrisBoard)
{
  m_previousStateOfBlocks = m_blocks;

  for (Block &block : m_blocks) {
    Index index = block.getIndex();
    index.setColumn(index.getColumn() - 1);
    block.setIndex(index);
  }

  if (isLegalMove(tetrisBoard)) {
    m_begin.setColumn(m_begin.getColumn() - 1);
    removeFrom(tetrisBoard);
    drawOn(tetrisBoard);
  } else {
    m_blocks = m_previousStateOfBlocks;
  }
}


void Tetromino::moveRight(TetrisBoard &tetrisBoard)
{
  m_previousStateOfBlocks = m_blocks;

  for (Block &block : m_blocks) {
    Index index = block.getIndex();
    index.setColumn(index.getColumn() + 1);
    block.setIndex(index);
  }

  if (isLegalMove(tetrisBoard)) {
    m_begin.setColumn(m_begin.getColumn() + 1);
    removeFrom(tetrisBoard);
    drawOn(tetrisBoard);
  } else {
    m_blocks = m_previousStateOfBlocks;
  }
}


void Tetromino::rotateLeft(TetrisBoard &tetrisBoard)
{
  m_previousStateOfBlocks = m_blocks;

  const int prevRotationIndex = m_rotationIndex++;
  if (m_rotationIndex == rotations.at(m_type).size()) {
    m_rotationIndex = 0;
  }

  const vector<Index> &rotation = rotations.at(m_type)[m_rotationIndex];
  for (int i = 0; i < rotation.size(); ++i) {
    m_blocks[i].setIndex(m_begin + rotation[i]);
  }

  if (isLegalMove(tetrisBoard)) {
    removeFrom(tetrisBoard);
    drawOn(tetrisBoard);
  } else {
    m_blocks = m_previousStateOfBlocks;
    m_rotationIndex = prevRotationIndex;
  }
}


// FIXME: Rotation methods have duplicate code!
void Tetromino::rotateRight(TetrisBoard &tetrisBoard)
{
  m_previousStateOfBlocks = m_blocks;

  const int prevRotationIndex = m_rotationIndex--;
  if (m_rotationIndex < 0) {
    m_rotationIndex = rotations.at(m_type).size() - 1;
  }

  const vector<Index> &rotation = rotations.at(m_type)[m_rotationIndex];
  for (int i = 0; i < rotation.size(); ++i) {
    m_blocks[i].setIndex(m_begin + rotation[i]);
  }

  if (isLegalMove(tetrisBoard)) {
    removeFrom(tetrisBoard);
    drawOn(tetrisBoard);
  } else {
    m_blocks = m_previousStateOfBlocks;
    m_rotationIndex = prevRotationIndex;
  }
}


void Tetromino::hardDrop(TetrisBoard &tetrisBoard)
{
  const int top = m_begin.getRow();
  const int bottom = tetrisBoard.rowCount();

  m_previousStateOfBlocks = m_blocks;

  for (int i = 1; i < bottom; ++i) {

    const vector<Block> lastLegalStateOfBlocks = m_blocks;

    for (Block &block : m_blocks) {
      Index index = block.getIndex();
      index.setRow(index.getRow() + 1);
      block.setIndex(index);
    }

    if (!isLegalMove(tetrisBoard)) {
      m_blocks = lastLegalStateOfBlocks;
      m_begin.setRow(m_begin.getRow() + i);
      removeFrom(tetrisBoard);
      drawOn(tetrisBoard);
      markAsLanded(tetrisBoard);
      emit landed();
      break;
    }
  }
}


void Tetromino::initBlocks(const QColor &color)
{
  for (const Index &blockIndex : rotations.at(m_type)[m_rotationIndex]) {
    m_blocks.push_back(Block {color, blockIndex + m_begin});
  }
}


bool Tetromino::isLegalMove(const TetrisBoard &tetrisBoard) const
{
  const int tetrisBoardRowCount = tetrisBoard.rowCount();
  const int tetrisBoardColumnCount = tetrisBoard.columnCount();

  for (const Block &block : m_blocks) {
    const Index index = block.getIndex();
    const int row = index.getRow();
    const int column = index.getColumn();

    if (row >= tetrisBoardRowCount || column < 0 ||
        column >= tetrisBoardColumnCount) {
      return false;
    } else if (tetrisBoard.hasBlockAt(index)) {
      const Block &block = tetrisBoard.getBlock(index);
      if (block.isLanded()) {
        return false;
      }
    }
  }

  return true;
}


void Tetromino::removeFrom(TetrisBoard &tetrisBoard)
{
  for (const Block &block : m_previousStateOfBlocks) {
    const Index index = block.getIndex();
    tetrisBoard.removeBlock(index);
  }
}


void Tetromino::markAsLanded(TetrisBoard &tetrisBoard)
{
  // This tetromino is going to be destroyed, so only the blocks of tetrisBoard
  // are updated.
  for (Block &block : m_blocks) {
    const Index index = block.getIndex();
    tetrisBoard.getBlock(index).landed(true);
  }
}
