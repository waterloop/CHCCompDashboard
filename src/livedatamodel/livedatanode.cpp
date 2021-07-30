#include "livedatamodel/livedatanode.h"

void LiveDataNode::slot_updateData(QVariant newData)
{
    data = newData;
    emit sig_dataUpdated();
}
