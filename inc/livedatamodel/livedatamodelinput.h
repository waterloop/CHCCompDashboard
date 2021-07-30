#ifndef LIVEDATAMODELINPUT_H
#define LIVEDATAMODELINPUT_H

#include <QList>
#include <QSharedPointer>
#include "livedatanode.h"

class LiveDataModelInput {
public:
    virtual QList<QSharedPointer<LiveDataNode>> enumerate() const = 0;
};

#endif // LIVEDATAMODELINPUT_H
