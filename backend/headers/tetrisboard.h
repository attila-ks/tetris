#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include "block.h"
#include "gameboard.h"
#include <QAbstractTableModel>
#include <QColor>

class TetrisBoard : public QAbstractTableModel
{
    Q_OBJECT

  public:
    /// @invariant @p rows and @p columns must be >= 0.
    TetrisBoard(const int rows, const int columns,
                const QColor& backgroundColor,
                QAbstractTableModel* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& modelIndex,
                  int role = Qt::DisplayRole) const override;

    void addBlock(const Block& block);
    void removeBlock(const Index& index);
    bool hasBlockAt(const Index& index) const;
    Block& getBlock(const Index& index);
    const Block& getBlock(const Index& index) const;

  private:
    Gameboard<Block> m_gameboard;
    QColor m_backgroundColor;
};

#endif
