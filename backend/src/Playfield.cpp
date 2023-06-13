#include "../headers/Playfield.h"
#include "../headers/FileError.h"
#include <fstream>

using namespace std;

Playfield::Playfield(const QColor emptyCellColor, QAbstractTableModel *parent) :
  QAbstractTableModel {parent},
  m_gameboard {},
  m_emptyCellColor {std::move(emptyCellColor)}
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
  const int row = modelIndex.row();
  const int column = modelIndex.column();

  if (hasBlockAt(row, column)) {
    const Block &block = m_gameboard(row, column).value();
    return role == FillColor ? block.getFillColor() : block.getBorderColor();
  } else {
    return m_emptyCellColor;
  }
}


void Playfield::addBlock(const Block block)
{
  const int row = block.getRow();
  const int column = block.getColumn();
  m_gameboard(row, column) = std::move(block);
  QModelIndex modelIndex = createIndex(row, column);
  emit dataChanged(modelIndex, modelIndex);
}


Block Playfield::removeBlock(const int row, const int column)
{
  optional<Block> &opt = m_gameboard(row, column);
  const Block &block = opt.value();
  opt = nullopt;
  QModelIndex modelIndex = createIndex(row, column);
  emit dataChanged(modelIndex, modelIndex);
  return block;
}


bool Playfield::hasBlockAt(const int row, const int column) const
{
  return m_gameboard(row, column).has_value();
}


Block &Playfield::operator()(const int row, const int column)
{
  return m_gameboard(row, column).value();
}


const Block &Playfield::operator()(const int row, const int column) const
{
  return m_gameboard(row, column).value();
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
      QModelIndex modelIndex = createIndex(opt->getRow(), opt->getColumn());
      opt = nullopt;
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
      const bool result = hasBlockAt(row, column);
      if (!result || (result && m_gameboard(row, column)->getType() !=
                                    Block::Type::Landed)) {
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
    removeBlock(row, column);
    QModelIndex modelIndex = createIndex(row, column);
    emit dataChanged(modelIndex, modelIndex);
  }
}


void Playfield::moveRowDown(const int row, const int offset)
{
  const int columns = columnCount();

  for (int column = 0; column < columns; ++column) {
    if (hasBlockAt(row, column) &&
        m_gameboard(row, column)->getType() == Block::Type::Landed) {
      Block block = removeBlock(row, column);
      block.setRow(row + offset);
      addBlock(block);
    }
  }
}
