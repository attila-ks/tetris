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
    Playfield(const QColor &emptyCellColor,
              QAbstractTableModel *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    enum ColorRoles { FillColor = Qt::UserRole + 1, BorderColor };

    QHash<int, QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &modelIndex,
                  int role = Qt::DisplayRole) const override;

    void addBlock(const Block &block);
    Block removeBlock(const Index &index);
    bool hasBlockAt(const Index &index) const;
    Block &getBlock(const Index &index);
    const Block &getBlock(const Index &index) const;

    /// @return the number of cleared rows, if any.
    int clearFilledRows();

  private:
    void clearFilledRow(const int row);
    void moveRowDown(const int row, const int offset);

    Gameboard<std::optional<Block>, 22, 10> m_gameboard;
    const QColor m_emptyCellColor;
};

#endif
