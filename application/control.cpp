#include "control.hpp"
#include "log/write"
// #include <launcher/launchersettings.hpp>
// #include <qguiapplication.h>
// #include <signal.h>
// #include <sysexits.h>

ApplicationControl::ApplicationControl(LauncherSettings const& )
    // :appExecPath(settings.appExecutablePath)
{
    connect(&appCurrentlyRunning,&bool_proxy::valueChanges,this,&ApplicationControl::currentlyRunningChanged);
}

void ApplicationControl::killApplication(){
    // logic
}

void ApplicationControl::startApplication(){
    
    cvk::write(clt::main) << cll::good << "application staring";
    // logic
}

void ApplicationControl::onProcessFinished(int , QProcess::ExitStatus )
{
  //logic
}
