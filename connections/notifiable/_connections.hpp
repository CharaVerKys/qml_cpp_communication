
// coredump.hpp
QObject::connect(
    this,&FrontendConnectionSide::sendCrashReportChanged,
    back_con, &BackendConnectionSide::sendCrashReportOptionChanged,
    Qt::QueuedConnection); //todo is it relevant to always queue implementation re-emit? maybe keep auto?