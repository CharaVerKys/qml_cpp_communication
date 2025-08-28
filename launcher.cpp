#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <filesystem>
#include <QQuickStyle>

#include <log/logger.hpp>
#include <log/qtintegration.hpp>

#include <connections/frontendconnectionside.hpp>
#include <singleapplication.hpp>
// #include <powercontrol/signalhandle.hpp>
// #include <launcher/emailclient.hpp>
// #include <launcher/launchersettings.hpp>
// #include <application/settings.hpp>
#include <application/control.hpp>
#include <sysexits.h>


int main(int argc, char** argv){

    std::filesystem::create_directory("your_log_dir");
    Logger::instance()->setLogDir("your_log_dir");
    Logger::instance()->init();
    cvk::write(clt::main) << cll::good << "log start";
    /*no caller*/::qInstallMessageHandler(qtReEntering);

    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    FrontendConnectionSide frontendConnectionSide(BackendConnectionSide::get());
    engine.rootContext()->setContextProperty("frontendConnectionSide", &frontendConnectionSide);

    engine.load(QUrl(QStringLiteral("qrc:/ApplicationWindow.qml")));
    cvk::write(clt::main) << cll::good << "qml engine loaded";
    
    QSharedMemory memory("<uniq id memory> 24SomeQuiteRandomText23QtMem_launcher");
    if(not singleApplication(&memory)){
        BackendConnectionSide::get()->showSingleApplication();
        app.exec(); // one of ~~three~~(two) exit points, no run app backend logic if not single application
        Logger::instance()->exit();
        std::exit(EX_TEMPFAIL);
    }
    
    // some deleted logic...
   
                                        // this is only for my public lib
                                        // funny that clang complain about 0, but not about 1 value
    ApplicationControl applicationControl{*((LauncherSettings*)1)};
    QObject::connect(BackendConnectionSide::get(),&BackendConnectionSide::restartApplicationAfterCrashChanged,
        &applicationControl,&ApplicationControl::switchRestartingApplication);
    QObject::connect(BackendConnectionSide::get(),&BackendConnectionSide::receivedStartApplication,
        &applicationControl,&ApplicationControl::startApplication);
    QObject::connect(&applicationControl,&ApplicationControl::currentlyRunningChanged,
        BackendConnectionSide::get(),&BackendConnectionSide::sendApplicationRunningChanged);
    QObject::connect(&applicationControl,&ApplicationControl::eventToUiLog,
        BackendConnectionSide::get(),&BackendConnectionSide::sendUiLogEvent);
    // QObject::connect(&applicationControl,&ApplicationControl::sendErrorToUi,
        // BackendConnectionSide::get(),&BackendConnectionSide::sendErrorQStringToUi);

    // other logic...

    int exit_code = app.exec();

    cvk::write(clt::main) << cll::good << "log end";
    Logger::instance()->exit();
    return exit_code;
}
