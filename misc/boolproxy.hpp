#pragma once

#include <qobject.h>

class bool_proxy : public QObject{
    Q_OBJECT
public:
    bool_proxy(bool b = false):v{b}{}

    operator bool(){
        return v;
    }
    bool operator=(const bool b){
        v = b;
        emit valueChanges(v);
        return v;
    }

signals:
    void valueChanges(bool);

private:
    bool v;
};