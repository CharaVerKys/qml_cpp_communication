signals:
    void receivedUiLogEvent(QString msg, bool highlightRed);
    void receivedCurrentlyRunningChanged(bool running);
public slots:
    void sendStartApplication(){
        cvk::write(clt::qt) << cll::debug << "sendWorks";
        INVOKE(back_con, &BackendConnectionSide::receivedStartApplication);
        // you can use connections and slots, but i find this syntax better for this code
        //                                                   in compare to QObject::connect
    }
    void sendRestartApplicationAfterCrashOption(const bool restart){
        INVOKE_ARGS(back_con, &BackendConnectionSide::restartApplicationAfterCrashChanged, Q_ARG(bool,restart));
    }