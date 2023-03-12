#include "../headers/tetrisboard.h"

using namespace std;

TetrisBoard::TetrisBoard(const int rows, const int columns,
                         const QColor& backgroundColor,
                         QAbstractTableModel* parent) :
  QAbstractTableModel {parent},
  m_gameboard {rows, columns},
  m_backgroundColor {backgroundColor}
{
}


int TetrisBoard::rowCount(const QModelIndex& parent) const
{
  return m_gameboard.getRows();
}


int TetrisBoard::columnCount(const QModelIndex& parent) const
{
  return m_gameboard.getColumns();
}


QVariant TetrisBoard::data(const QModelIndex& modelIndex, int role) const
{
  const Index index = {modelIndex.row(), modelIndex.column()};

  if (m_gameboard.hasItemAt(index))
  {
    const Block& block = m_gameboard.getItem(index);
    return block.getColor();
  }
  else
  {
    return QVariant {m_backgroundColor};
  }
}


void TetrisBoard::addBlock(const Block& block)
{
  const Index index = block.getIndex();
  m_gameboard.addItem(block, index);
  QModelIndex modelIndex = createIndex(index.getRow(), index.getColumn());
  emit dataChanged(modelIndex, modelIndex);
}


void TetrisBoard::removeBlock(const Index& index)
{
  m_gameboard.removeItem(index);
  QModelIndex modelIndex = createIndex(index.getRow(), index.getColumn());
  emit dataChanged(modelIndex, modelIndex);
}


bool TetrisBoard::hasBlockAt(const Index& index) const
{
  return m_gameboard.hasItemAt(index);
}


Block& TetrisBoard::getBlock(const Index& index)
{
  return m_gameboard.getItem(index);
}


const Block& TetrisBoard::getBlock(const Index& index) const
{
  return m_gameboard.getItem(index);
}
