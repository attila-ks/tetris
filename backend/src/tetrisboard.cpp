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


QVariant TetrisBoard::data(const QModelIndex& index, int role) const
{
  const Position position = {index.row(), index.column()};

  if (m_gameboard.hasItemAt(position))
  {
    const Block& block = m_gameboard.getItem(position);
    return block.getColor();
  }
  else
  {
    return QVariant {m_backgroundColor};
  }
}


void TetrisBoard::addBlock(const Block& block, const Position& position)
{
  m_gameboard.addItem(block, position);
  auto index = createIndex(position.getRow(), position.getColumn());
  emit dataChanged(index, index);
}


void TetrisBoard::removeBlock(const Position& position)
{
  m_gameboard.removeItem(position);
  auto index = createIndex(position.getRow(), position.getColumn());
  emit dataChanged(index, index);
}


bool TetrisBoard::hasBlockAt(const Position& position) const
{
  return m_gameboard.hasItemAt(position);
}


Block& TetrisBoard::getBlock(const Position& position)
{
  return m_gameboard.getItem(position);
}


const Block& TetrisBoard::getBlock(const Position& position) const
{
  return m_gameboard.getItem(position);
}
