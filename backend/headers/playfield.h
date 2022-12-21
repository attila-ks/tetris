#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <QAbstractTableModel>
#include <QColor>
#include <vector>

class Playfield : public QAbstractTableModel
{
    Q_OBJECT

  public:
    Playfield(const size_t rows, const size_t columns,
              const QColor& backgroundColor);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index,
                  int role = Qt::DisplayRole) const override;

  private:
    struct Cell
    {
        QColor m_color;
    };

  private:
    size_t m_rows;
    size_t m_columns;
    QColor m_backgroundColor;
    std::vector<std::vector<Cell>> m_data;
};

#endif
