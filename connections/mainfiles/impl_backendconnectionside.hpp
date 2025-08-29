#pragma once
#include <qobject.h>

#include "../signalslot/_types.hpp"

class BackendConnectionSide : public QObject{
    Q_OBJECT
public:
    BackendConnectionSide(); 
    static BackendConnectionSide* get(){static BackendConnectionSide b; return &b;}

signals:
    #insert backend emits

    #paste "../back.list"
};