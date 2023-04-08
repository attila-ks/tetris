#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include "block.h"
#include "gameboard.h"
#include <QAbstractTableModel>
#include <QColor>

class Playfield : public QAbstractTableModel
{
    Q_OBJECT

  public:
    /// @invariant @p rows and @p columns must be >= 0.
    Playfield(const int rows, const int columns, const QColor &backgroundColor,
              QAbstractTableModel *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &modelIndex,
                  int role = Qt::DisplayRole) const override;

    void addBlock(const Block &block);
    Block removeBlock(const Index &index);
    bool hasLandedBlockAt(const Index &index) const;
    Block &getBlock(const Index &index);
    const Block &getBlock(const Index &index) const;

    /// @return the number of cleared rows, if any.
    int clearFilledRows();

  private:
    void clearFilledRow(const int row);
    void moveRowDown(const int row, const int offset);

    Gameboard<Block> m_gameboard;
    const QColor m_backgroundColor;
};

#endif
