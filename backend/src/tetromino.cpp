#include "../headers/tetromino.h"
#include "../headers/Playfield.h"
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


Tetromino::Tetromino(const Type type, const QColor &fillColor,
                     const QColor &borderColor, const Index &begin) :
  Tetromino(type, Block::Type::Falling, fillColor, borderColor, begin)
{
}


Tetromino::Type Tetromino::getType() const
{
  return m_type;
}


const Index &Tetromino::getBegin() const
{
  return m_begin;
}


const vector<Block> &Tetromino::getBlocks() const
{
  return m_blocks;
}


const QColor &Tetromino::getBorderColor() const
{
  return m_blocks[0].getBorderColor();
}


int Tetromino::getRotationIndex() const
{
  return m_rotationIndex;
}


void Tetromino::drawOn(Playfield &playfield) const
{
  for (const Block &block : m_blocks) {
    playfield.addBlock(block);
  }
}


void Tetromino::moveDown(Playfield &playfield)
{
  m_previousStateOfBlocks = m_blocks;

  for (Block &block : m_blocks) {
    const Index &index = block.getIndex();
    block.setIndex(Index {index.getRow() + 1, index.getColumn()});
  }

  if (isLegalMove(playfield)) {
    m_begin.setRow(m_begin.getRow() + 1);
    removeFrom(playfield);
    drawOn(playfield);
  } else {
    m_blocks = m_previousStateOfBlocks;
    markAsLanded(playfield);
    emit landed();
  }
}


void Tetromino::moveLeft(Playfield &playfield)
{
  m_previousStateOfBlocks = m_blocks;

  for (Block &block : m_blocks) {
    const Index &index = block.getIndex();
    block.setIndex(Index {index.getRow(), index.getColumn() - 1});
  }

  if (isLegalMove(playfield)) {
    m_begin.setColumn(m_begin.getColumn() - 1);
    removeFrom(playfield);
    drawOn(playfield);
  } else {
    m_blocks = m_previousStateOfBlocks;
  }
}


void Tetromino::moveRight(Playfield &playfield)
{
  m_previousStateOfBlocks = m_blocks;

  for (Block &block : m_blocks) {
    const Index &index = block.getIndex();
    block.setIndex(Index {index.getRow(), index.getColumn() + 1});
  }

  if (isLegalMove(playfield)) {
    m_begin.setColumn(m_begin.getColumn() + 1);
    removeFrom(playfield);
    drawOn(playfield);
  } else {
    m_blocks = m_previousStateOfBlocks;
  }
}


void Tetromino::rotateLeft(Playfield &playfield)
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

  if (isLegalMove(playfield)) {
    removeFrom(playfield);
    drawOn(playfield);
  } else {
    m_blocks = m_previousStateOfBlocks;
    m_rotationIndex = prevRotationIndex;
  }
}


// FIXME: Rotation methods have duplicate code!
void Tetromino::rotateRight(Playfield &playfield)
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

  if (isLegalMove(playfield)) {
    removeFrom(playfield);
    drawOn(playfield);
  } else {
    m_blocks = m_previousStateOfBlocks;
    m_rotationIndex = prevRotationIndex;
  }
}


void Tetromino::hardDrop(Playfield &playfield)
{
  const int top = m_begin.getRow();
  const int bottom = playfield.rowCount();

  m_previousStateOfBlocks = m_blocks;

  for (int i = 1; i < bottom; ++i) {

    const vector<Block> lastLegalStateOfBlocks = m_blocks;

    for (Block &block : m_blocks) {
      const Index &index = block.getIndex();
      block.setIndex(Index {index.getRow() + 1, index.getColumn()});
    }

    if (!isLegalMove(playfield)) {
      m_blocks = lastLegalStateOfBlocks;
      m_begin.setRow(m_begin.getRow() + i);
      removeFrom(playfield);
      drawOn(playfield);
      markAsLanded(playfield);
      emit landed();
      break;
    }
  }
}


Tetromino::Tetromino(const Type type, const Block::Type blockType,
                     const QColor &fillColor, const QColor &borderColor,
                     const Index &begin) :
  m_type {type},
  m_begin {begin},
  m_blocks {},
  m_previousStateOfBlocks {},
  m_rotationIndex {0}
{
  initBlocks(blockType, fillColor, borderColor);
}


bool Tetromino::isLegalMove(const Playfield &playfield) const
{
  const int playfieldRowCount = playfield.rowCount();
  const int playfieldColumnCount = playfield.columnCount();

  for (const Block &block : m_blocks) {
    const Index &index = block.getIndex();
    const int row = index.getRow();
    const int column = index.getColumn();

    if (row >= playfieldRowCount || column < 0 ||
        column >= playfieldColumnCount) {
      return false;
    } else if (playfield.hasBlockAt(index) &&
               playfield.getBlock(index).getType() == Block::Type::Landed) {
      return false;
    }
  }

  return true;
}


void Tetromino::removeFrom(Playfield &playfield)
{
  for (const Block &block : m_previousStateOfBlocks) {
    const Index &index = block.getIndex();
    playfield.removeBlock(index);
  }
}


void Tetromino::initBlocks(const Block::Type type, const QColor &fillColor,
                           const QColor &borderColor)
{
  for (const Index &blockIndex : rotations.at(m_type)[m_rotationIndex]) {
    m_blocks.push_back(
        Block {type, fillColor, borderColor, blockIndex + m_begin});
  }
}


void Tetromino::markAsLanded(Playfield &playfield)
{
  // This tetromino is going to be destroyed, so only the blocks of playfield
  // are updated.
  for (Block &block : m_blocks) {
    const Index &index = block.getIndex();
    playfield.getBlock(index).setType(Block::Type::Landed);
  }
}
