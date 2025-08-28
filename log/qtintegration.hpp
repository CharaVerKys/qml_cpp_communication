
#include <qglobal.h>
#include <qregularexpression.h>
#include <log/write>

inline void qtReEntering(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static const QRegularExpression rx = QRegularExpression("([\\w-]+::[\\w-]+)");
    const QRegularExpressionMatch mt = rx.match(context.function);
    QString function = mt.hasMatch() ? mt.captured(0) : context.function;

    cll level;
    switch (type) {
        case QtDebugMsg:    level = cll::norm;    break;
        case QtInfoMsg:     level = cll::norm;     break;
        case QtWarningMsg:  level = cll::error;    break;
        case QtCriticalMsg: level = cll::critical; break;
        case QtFatalMsg:    level = cll::critical; break;
    }

    constexpr const char* funcColor = "\033[35m"; 
    const char* prevColor = "\033[0m";
    switch (level) {
        case cll::debug:    prevColor = "\033[36m"; break;
        case cll::good:     prevColor = "\033[32m"; break;
        case cll::norm:     prevColor = "\033[0m";  break;
        case cll::error:    prevColor = "\033[33m"; break;
        case cll::critical: prevColor = "\033[31m"; break;
    }

    cvk::write(clt::qt) << level 
           << funcColor << "[ " << function.toUtf8().constData() << " ] -> "
           << prevColor << msg.toUtf8().constData();
}

//    /*no caller*/::qInstallMessageHandler(qtReEntering);