#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include "block.h"
#include <QAbstractTableModel>
#include <QColor>
#include <optional>
#include <vector>

class Playfield : public QAbstractTableModel
{
    Q_OBJECT

  public:
    Playfield(const size_t rows, const size_t columns,
              const QColor& backgroundColor,
              QAbstractTableModel* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index,
                  int role = Qt::DisplayRole) const override;

    void addBlocks(const std::vector<Block>& blocks);

    bool removeBlockAt(const Position& position);

    bool hasBlockAt(const Position& position) const;

    /// @pre hasBlockAt(const Position& position) must be called for the
    /// @p position before calling this method!
    const Block& getBlockAt(const Position& position) const;

  private:
    struct Cell
    {
        static QColor m_color;
        std::optional<Block> m_block;
    };

  private:
    size_t m_rows;
    size_t m_columns;
    std::vector<std::vector<Cell>> m_data;
};

#endif
