#include "../headers/Playfield.h"

using namespace std;

Playfield::Playfield(const int rows, const int columns,
                     const QColor &backgroundColor,
                     QAbstractTableModel *parent) :
  QAbstractTableModel {parent},
  m_gameboard {rows, columns},
  m_backgroundColor {backgroundColor}
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


QVariant Playfield::data(const QModelIndex &modelIndex, int role) const
{
  const Index index = {modelIndex.row(), modelIndex.column()};

  if (m_gameboard.hasItemAt(index)) {
    const Block &block = m_gameboard.getItem(index);
    return block.getColor();
  } else {
    return QVariant {m_backgroundColor};
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


bool Playfield::hasLandedBlockAt(const Index &index) const
{
  if (!m_gameboard.hasItemAt(index)) {
    return false;
  }

  const Block &block = m_gameboard.getItem(index);
  return block.isLanded();
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

  for (int row = bottom; row >= top;) {
    int filledColumnCounter = 0;

    for (int column = 0; column < columns; ++column) {
      if (!hasLandedBlockAt({row, column})) {
        break;
      }

      ++filledColumnCounter;
    }

    if (filledColumnCounter == 0) {
      break;
    } else if (filledColumnCounter == columns) {
      clearFilledRow(row);
      moveBlocksDown(row);
      ++clearedRowCounter;
    } else {
      --row;
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


void Playfield::moveBlocksDown(const int clearedRow)
{
  const int columns = columnCount();

  for (int row = clearedRow; row >= 0; --row) {
    int filledColumnCounter = 0;

    for (int column = 0; column < columns; ++column) {
      Index index {row - 1, column};
      if (hasLandedBlockAt(index)) {
        Block block = removeBlock(index);
        index.setRow(index.getRow() + 1);
        block.setIndex(index);
        addBlock(block);
        ++filledColumnCounter;
      }
    }

    if (filledColumnCounter == 0) {
      break;
    }
  }
}
