#include "impl_frontendconnectionside.hpp"

FrontendConnectionSide::FrontendConnectionSide(BackendConnectionSide* back){
    checkThread(&mainThreadID);
    assert(back);
    back_con = back;
// bound qthread of backend may be different, but if use non direct for backendCon <-> backendModules it is negligible

    #insert notify connections

    #insert frontend connections
}