#pragma once
#include <qobject.h>

#include "../signalslot/_types.hpp"

class BackendConnectionSide : public QObject{
    Q_OBJECT
public:
    BackendConnectionSide(); // cpp file to prevent including moc in every single cpp in this project
    static BackendConnectionSide* get(){static BackendConnectionSide b; return &b;}

signals:
    #paste "../notifiable/_backedreemits.hpp"

    #paste "../back.list"
};