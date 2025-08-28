#pragma once

#include <qobject.h>
#include <filesystem>
#include <boolproxy.hpp>
#include <qprocess.h>

class LauncherSettings;

class ApplicationControl : public QObject{
    Q_OBJECT
public:
    ApplicationControl(LauncherSettings const&);

public slots:
    void switchRestartingApplication(const bool b){restartApplicationOnCrash = b;}
    void killApplication();
    void startApplication();

signals:
    void currentlyRunningChanged(const bool); // ? bool proxy
    void applicationCrashed(std::optional<std::string> path_to_core_dump, std::string application_cout_and_cerr);
    void eventToUiLog(QString eventText, bool highlightRed);
    void sendErrorToUi(const QString);

private slots:
    void onProcessFinished(int exitCode, QProcess::ExitStatus);

private:
    //todo later
    std::optional<std::string> findCoreDump(){return std::nullopt;}
    bool normalExitCodes(int exitCode);

private:
    bool_proxy appCurrentlyRunning = false; // ? proxy to signal currentlyRunningChanged
    bool restartApplicationOnCrash = true;
    const std::filesystem::path appExecPath;
    std::ostringstream cout_and_cerr;

    std::unique_ptr<QProcess> appProcess; // ? cross platform
};