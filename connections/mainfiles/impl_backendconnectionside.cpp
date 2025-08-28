#include "impl_backendconnectionside.hpp"
#include "threadchecking.hpp"
BackendConnectionSide::BackendConnectionSide(){checkThread(&mainThreadID);}
// #include "automatic.include.moc"