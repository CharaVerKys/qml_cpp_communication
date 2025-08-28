#include "frontendconnectionside.hpp"

FrontendConnectionSide::FrontendConnectionSide(BackendConnectionSide* back){
    checkThread(&mainThreadID);
    assert(back);
    back_con = back;
// bound qthread of backend may be different, but if use non direct for backendCon <-> backendModules it is negligible

// connect notify to backend with queued con, without magic
// connect(this,&notifyBackend,backend,&receiveFunc,Qt::queued...)
#paste "../notifiable/_connections.hpp"

#paste "../signalslot/_connections.hpp"

}