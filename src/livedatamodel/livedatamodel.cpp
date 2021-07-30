#include "livedatamodel/livedatamodel.h"

LiveDataModel::LiveDataModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}

////////////////////////////////////////////////////
///
///      QAbstractItemModel Implimentaitons
///
////////////////////////////////////////////////////
QModelIndex LiveDataModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if (row > rowCount() || column > columnCount())
    {
        return QModelIndex();
    }

    return createIndex(row, column);
}

QModelIndex LiveDataModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QModelIndex();
}

int LiveDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.length(); // Temp, need to figure this out in the future
}

int LiveDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1; // Single column list
}

QVariant LiveDataModel::data(const QModelIndex &index, int role) const
{
    QSharedPointer<LiveDataNode> node = m_data.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
        return node->name;
    case DataRole:
        return node->data;
    case UnitRole:
        return node->unit;
    case MinValueRole:
        return node->safeRange.min;
    case MaxValueRole:
        return node->safeRange.max;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> LiveDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Qt::DisplayRole, "display");
    roles.insert(DataRole, "reading");
    roles.insert(UnitRole, "unit");
    roles.insert(MaxValueRole, "max_value");
    roles.insert(MinValueRole, "min_value");
    return roles;
}

////////////////////////////////////////////////////
///
///      Public Api Methods
///
////////////////////////////////////////////////////
void LiveDataModel::insertData(LiveDataModelInput& input)
{
    QList<QSharedPointer<LiveDataNode>> newData = input.enumerate();
    beginInsertRows(QModelIndex(), m_data.length(), newData.length());
    for (QList<QSharedPointer<LiveDataNode>>::iterator runner = newData.begin(); runner != newData.end(); runner++)
    {
        m_data.append(*runner);
        QObject::connect(runner->get(), &LiveDataNode::sig_dataUpdated, [=]() {
            emit dataChanged(createIndex(m_data.length()-1, 0), createIndex(m_data.length()-1, 0));
        });
    }
    endInsertRows();
}
