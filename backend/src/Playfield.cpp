#include "../headers/Playfield.h"

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
    const Block &block = m_gameboard.getItem(index);
    return role == FillColor ? block.getFillColor() : block.getBorderColor();
  } else {
    return m_emptyCellColor;
  }
}


void Playfield::addBlock(const Block &block)
{
  const Index index = block.getIndex();
  m_gameboard.addItem(block, index);
  QModelIndex modelIndex = createIndex(index.getRow(), index.getColumn());
  emit dataChanged(modelIndex, modelIndex);
}


Block Playfield::removeBlock(const Index &index)
{
  const Block block = m_gameboard.removeItem(index);
  QModelIndex modelIndex = createIndex(index.getRow(), index.getColumn());
  emit dataChanged(modelIndex, modelIndex);
  return block;
}


bool Playfield::hasBlockAt(const Index &index) const
{
  return m_gameboard.hasItemAt(index);
}


Block &Playfield::getBlock(const Index &index)
{
  return m_gameboard.getItem(index);
}


const Block &Playfield::getBlock(const Index &index) const
{
  return m_gameboard.getItem(index);
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
