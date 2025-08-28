#pragma once
#include <connections/mainfiles/impl_backendconnectionside.hpp>
#include <misc/qtinvokemethod.hpp>
#include <misc/threadchecking.hpp> // IWYU pragma: keep 

// types for notify
#include <connections/notifiable/_types.hpp>

class FrontendConnectionSide : public QObject{
    Q_OBJECT
public:
    FrontendConnectionSide(BackendConnectionSide* back);

    #paste "../notifiable.list"

    #paste "../front.list"

private:
    BackendConnectionSide* back_con;
};