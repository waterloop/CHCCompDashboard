#ifndef LIVEDATAMODEL_H
#define LIVEDATAMODEL_H

#include <QAbstractItemModel>
#include <QList>
#include <QSharedPointer>
#include "livedatamodelinput.h"

/////////////////////////////////////////////////
/// \brief The LiveDataModel class
/// The Live Data model is responsible for
/// providing an interface from the various Pod
/// System models so that the information can be
/// displayed through QML views
/////////////////////////////////////////////////
class LiveDataModel : public QAbstractItemModel
{
public:
    explicit LiveDataModel(QObject *parent=nullptr);

    /**
     *
     * Required Functions for Subclass of QAbstractItemModel
     *
     */
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    void insertData(LiveDataModelInput& input);

private:
    QList<QSharedPointer<LiveDataNode>> m_data;

    enum LiveDataRoles {
        DataRole = Qt::UserRole, // All role enums must be >= UserRole
        UnitRole,
        MaxValueRole,
        MinValueRole
    };
};

#endif // LIVEDATAMODEL_H
