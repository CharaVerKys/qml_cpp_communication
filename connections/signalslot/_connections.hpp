// ? btw if using INVOKE macros, then no frontend->backend required
// ? everything here may be list of backend->frontend

// show single application.hpp
QObject::connect(
    back_con,&BackendConnectionSide::showSingleApplication,
    this, &FrontendConnectionSide::showSingleApplicationDialog,
    Qt::QueuedConnection); 
