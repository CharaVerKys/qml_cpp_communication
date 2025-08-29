signals:
    void receiveUiLogEvent(QString msg, bool highlightRed);
public slots: 
    void receiveApplicationRunningChanged(const bool running){
        setAppRunningState(running);
    }
private: // '_connectBackendToSignals()' for reflection
    void appControl_connectBackendToSignals(){
        connect(
            back_con,&BackendConnectionSide::sendApplicationRunningChanged,
            this,&FrontendConnectionSide::receiveApplicationRunningChanged,
            Qt::QueuedConnection); 
        connect(
            back_con,&BackendConnectionSide::sendUiLogEvent,
            this,&FrontendConnectionSide::receiveUiLogEvent,
            Qt::QueuedConnection); 
    }