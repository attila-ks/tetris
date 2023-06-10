#include "../headers/Playfield.h"
#include "../headers/FileError.h"
#include <fstream>

using namespace std;

Playfield::Playfield(const QColor &emptyCellColor,
                     QAbstractTableModel *parent) :
  QAbstractTableModel {parent},
  m_gameboard {},
  m_emptyCellColor {emptyCellColor}
{
}


int Playfield::rowCount(const QModelIndex &parent) const
{
  return m_gameboard.getRows();
}


int Playfield::columnCount(const QModelIndex &parent) const
{
  return m_gameboard.getColumns();
}


QHash<int, QByteArray> Playfield::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[FillColor] = "fillColor";
  roles[BorderColor] = "borderColor";
  return roles;
}


QVariant Playfield::data(const QModelIndex &modelIndex, int role) const
{
  const Index index = {modelIndex.row(), modelIndex.column()};

  if (hasBlockAt(index)) {
    const Block &block = m_gameboard(index.getRow(), index.getColumn()).value();
    return role == FillColor ? block.getFillColor() : block.getBorderColor();
  } else {
    return m_emptyCellColor;
  }
}


// FIXME: param `block` is moved while it's a reference.
void Playfield::addBlock(const Block &block)
{
  const Index index = block.getIndex();
  m_gameboard(index.getRow(), index.getColumn()) = std::move(block);
  QModelIndex modelIndex = createIndex(index.getRow(), index.getColumn());
  emit dataChanged(modelIndex, modelIndex);
}


Block Playfield::removeBlock(const Index &index)
{
  optional<Block> &opt = m_gameboard(index.getRow(), index.getColumn());
  const Block &block = opt.value();
  opt = nullopt;
  QModelIndex modelIndex = createIndex(index.getRow(), index.getColumn());
  emit dataChanged(modelIndex, modelIndex);
  return block;
}


bool Playfield::hasBlockAt(const Index &index) const
{
  return m_gameboard(index.getRow(), index.getColumn()).has_value();
}


Block &Playfield::getBlock(const Index &index)
{
  return m_gameboard(index.getRow(), index.getColumn()).value();
}


const Block &Playfield::getBlock(const Index &index) const
{
  return m_gameboard(index.getRow(), index.getColumn()).value();
}


std::ofstream &operator<<(std::ofstream &ofstream, const Playfield &playfield)
{
  for (const optional<Block> &opt : playfield.m_gameboard) {
    if (opt.has_value()) {
      ofstream << opt.value() << '\n';
    } else {
      ofstream << "nullopt\n";
    }
    if (!ofstream) {
      throw FileError {"An error occurred while saving the playfield."};
    }
  }

  return ofstream;
}


std::ifstream &operator>>(std::ifstream &ifstream, Playfield &playfield)
{
  Block block;
  string line;
  int loadedItemCounter = 0;
  const int gameboardSize =
      playfield.m_gameboard.getRows() * playfield.m_gameboard.getColumns();

  while (getline(ifstream, line) && loadedItemCounter < gameboardSize) {
    if (line != "nullopt") {
      istringstream istrstream {line};
      istrstream >> block;
      playfield.addBlock(std::move(block));
    }

    ++loadedItemCounter;
  }

  if (!ifstream.eof()) {
    throw FileError {"Excess data in the file while loading the playfield."};
  } else if (ifstream.eof() && loadedItemCounter < gameboardSize) {
    throw FileError {"Missing data from the file while loading the playfield."};
  }

  return ifstream;
}


void Playfield::clear()
{
  for (optional<Block> &opt : m_gameboard) {
    if (opt.has_value()) {
      const Index &index = opt->getIndex();
      opt = nullopt;
      QModelIndex modelIndex = createIndex(index.getRow(), index.getColumn());
      emit dataChanged(modelIndex, modelIndex);
    }
  }
}


int Playfield::clearFilledRows()
{
  const int top = 0;
  const int bottom = rowCount() - 1;
  const int columns = columnCount();
  int clearedRowCounter = 0;

  for (int row = bottom; row >= top; --row) {
    int blockCounter = 0;

    for (int column = 0; column < columns; ++column) {
      const Index index {row, column};
      const bool result = hasBlockAt(index);
      if (!result ||
          (result && getBlock(index).getType() != Block::Type::Landed)) {
        break;
      }

      ++blockCounter;
    }

    if (blockCounter == columns) {
      clearFilledRow(row);
      ++clearedRowCounter;
    } else if (clearedRowCounter > 0) {
      moveRowDown(row, clearedRowCounter);
    }
  }

  return clearedRowCounter;
}


void Playfield::clearFilledRow(const int row)
{
  const int columns = columnCount();
  for (int column = 0; column < columns; ++column) {
    const Index index {row, column};
    removeBlock(index);
    QModelIndex modelIndex = createIndex(index.getRow(), index.getColumn());
    emit dataChanged(modelIndex, modelIndex);
  }
}


void Playfield::moveRowDown(const int row, const int offset)
{
  const int columns = columnCount();

  for (int column = 0; column < columns; ++column) {
    Index index {row, column};
    if (hasBlockAt(index) && getBlock(index).getType() == Block::Type::Landed) {
      Block block = removeBlock(index);
      index.setRow(index.getRow() + offset);
      block.setIndex(index);
      addBlock(block);
    }
  }
}
