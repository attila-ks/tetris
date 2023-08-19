#include "../headers/tetromino.h"
#include "../headers/FileError.h"
#include "../headers/Playfield.h"
#include <fstream>
#include <map>

using namespace std;

// Helper functions
void saveBlocks(ofstream &ofstream, const vector<Block> &blocks);
void loadBlocks(ifstream &ifstream, vector<Block> &blocks);


static const map<Tetromino::Type, vector<vector<pair<int, int>>>> rotations {
    {Tetromino::Type::I,
     {{{0, 0}, {0, 1}, {0, 2}, {0, 3}},
      {{-1, 2}, {0, 2}, {1, 2}, {2, 2}},
      {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
      {{-1, 1}, {0, 1}, {1, 1}, {2, 1}}}},
    {Tetromino::Type::J,
     {{{0, 0}, {1, 0}, {1, 1}, {1, 2}},
      {{0, 1}, {0, 2}, {1, 1}, {2, 1}},
      {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
      {{0, 1}, {1, 1}, {2, 0}, {2, 1}}}},
    {Tetromino::Type::L,
     {{{0, 2}, {1, 0}, {1, 1}, {1, 2}},
      {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
      {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
      {{0, 0}, {0, 1}, {1, 1}, {2, 1}}}},
    {Tetromino::Type::O, {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}}},
    {Tetromino::Type::S,
     {{{0, 1}, {0, 2}, {1, 0}, {1, 1}},
      {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
      {{1, 1}, {1, 2}, {2, 0}, {2, 1}},
      {{0, 0}, {1, 0}, {1, 1}, {2, 1}}}},
    {Tetromino::Type::T,
     {{{0, 1}, {1, 0}, {1, 1}, {1, 2}},
      {{0, 1}, {1, 1}, {1, 2}, {2, 1}},
      {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
      {{0, 1}, {1, 0}, {1, 1}, {2, 1}}}},
    {Tetromino::Type::Z,
     {{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
      {{0, 2}, {1, 1}, {1, 2}, {2, 1}},
      {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
      {{0, 1}, {1, 0}, {1, 1}, {2, 0}}}}};


Tetromino::Tetromino(const Type type, const QColor &fillColor,
                     const QColor &borderColor, const int row,
                     const int column) :
  Tetromino(type, Block::Type::Falling, fillColor, borderColor, row, column)
{
}


void Tetromino::clear()
{
  m_blocks.clear();
}


Tetromino::Type Tetromino::getType() const
{
  return m_type;
}


int Tetromino::getRow() const
{
  return m_row;
}


int Tetromino::getColumn() const
{
  return m_column;
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


bool Tetromino::isLanded() const
{
  return m_isLanded;
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
    block.setRow(block.getRow() + 1);
  }

  if (isLegalMove(playfield)) {
    ++m_row;
    removeFrom(playfield);
    drawOn(playfield);
  } else {
    m_blocks = m_previousStateOfBlocks;
    markAsLanded(playfield);
    m_isLanded = true;
  }
}


void Tetromino::moveLeft(Playfield &playfield)
{
  m_previousStateOfBlocks = m_blocks;

  for (Block &block : m_blocks) {
    block.setColumn(block.getColumn() - 1);
  }

  if (isLegalMove(playfield)) {
    --m_column;
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
    block.setColumn(block.getColumn() + 1);
  }

  if (isLegalMove(playfield)) {
    ++m_column;
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

  const vector<pair<int, int>> &rotation =
      rotations.at(m_type)[m_rotationIndex];
  for (int i = 0; i < rotation.size(); ++i) {
    const auto [row, column] = rotation[i];
    m_blocks[i].setRow(m_row + row);
    m_blocks[i].setColumn(m_column + column);
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

  const vector<pair<int, int>> &rotation =
      rotations.at(m_type)[m_rotationIndex];
  for (int i = 0; i < rotation.size(); ++i) {
    const auto [row, column] = rotation[i];
    m_blocks[i].setRow(m_row + row);
    m_blocks[i].setColumn(m_column + column);
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
  const int bottom = playfield.rowCount();

  m_previousStateOfBlocks = m_blocks;

  for (int i = 1; i < bottom; ++i) {

    const vector<Block> lastLegalStateOfBlocks = m_blocks;

    for (Block &block : m_blocks) {
      block.setRow(block.getRow() + 1);
    }

    if (!isLegalMove(playfield)) {
      m_blocks = lastLegalStateOfBlocks;
      m_row += i;
      removeFrom(playfield);
      drawOn(playfield);
      markAsLanded(playfield);
      m_isLanded = true;
      break;
    }
  }
}


ofstream &operator<<(ofstream &ofstream, const Tetromino &tetromino)
{
  ofstream << static_cast<int>(tetromino.m_type) << ' ' << tetromino.m_row
           << ' ' << tetromino.m_column << '\n';

  if (!ofstream) {
    throw FileError {"An error occurred while saving the tetromino."};
  }

  saveBlocks(ofstream, tetromino.m_blocks);
  ofstream << '\n';
  saveBlocks(ofstream, tetromino.m_previousStateOfBlocks);

  ofstream << '\n' << tetromino.m_rotationIndex;
  if (!ofstream) {
    throw FileError {"An error occurred while saving the tetromino."};
  }

  return ofstream;
}


ifstream &operator>>(ifstream &ifstream, Tetromino &tetromino)
{
  int type;
  int beginRow;
  int beginColumn;
  ifstream >> type >> beginRow >> beginColumn;

  if (!ifstream) {
    throw FileError {"An error occurred while loading the tetromino."};
  }

  tetromino.m_type = static_cast<Tetromino::Type>(type);
  tetromino.m_row = beginRow;
  tetromino.m_column = beginColumn;

  loadBlocks(ifstream, tetromino.m_blocks);
  loadBlocks(ifstream, tetromino.m_previousStateOfBlocks);

  ifstream >> tetromino.m_rotationIndex;
  if (!ifstream) {
    throw FileError {"An error occurred while loading the tetromino."};
  }

  return ifstream;
}


Tetromino::Tetromino(const Type type, const Block::Type blockType,
                     const QColor &fillColor, const QColor &borderColor,
                     const int row, const int column, const int rotationIndex) :
  m_type {type},
  m_row {row},
  m_column {column},
  m_blocks {},
  m_previousStateOfBlocks {},
  m_rotationIndex {rotationIndex}
{
  initBlocks(blockType, fillColor, borderColor);
}


bool Tetromino::isLegalMove(const Playfield &playfield) const
{
  const int playfieldRowCount = playfield.rowCount();
  const int playfieldColumnCount = playfield.columnCount();

  for (const Block &block : m_blocks) {
    const int row = block.getRow();
    const int column = block.getColumn();

    if (row >= playfieldRowCount || column < 0 ||
        column >= playfieldColumnCount) {
      return false;
    } else if (playfield.hasLandedBlockAt(row, column)) {
      return false;
    }
  }

  return true;
}


void Tetromino::removeFrom(Playfield &playfield)
{
  for (const Block &block : m_previousStateOfBlocks) {
    playfield.removeBlock(block.getRow(), block.getColumn());
  }
}


void Tetromino::initBlocks(const Block::Type type, const QColor &fillColor,
                           const QColor &borderColor)
{
  for (const auto [row, column] : rotations.at(m_type)[m_rotationIndex]) {
    m_blocks.push_back(
        Block {type, fillColor, borderColor, m_row + row, m_column + column});
  }
}


inline void Tetromino::markAsLanded(Playfield &playfield)
{
  // This tetromino is going to be destroyed, so only the blocks of playfield
  // are updated.
  for (const Block &block : m_blocks) {
    playfield(block.getRow(), block.getColumn()).setType(Block::Type::Landed);
  }
}


void saveBlocks(ofstream &ofstream, const vector<Block> &blocks)
{
  ofstream << blocks.size() << '\n';

  for (const Block &block : blocks) {
    ofstream << block << ' ';
    if (!ofstream) {
      throw FileError {"An error occurred while saving the tetromino blocks."};
    }
  }
}


void loadBlocks(ifstream &ifstream, vector<Block> &blocks)
{
  size_t size;
  ifstream >> size;

  blocks.reserve(size);

  Block block;
  for (size_t i = 0; i < size; ++i) {
    if (!(ifstream >> block)) {
      throw FileError {"An error occurred while loading the tetromino blocks."};
    }

    blocks.push_back(std::move(block));
  }
}
