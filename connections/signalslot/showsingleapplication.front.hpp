signals:
    void receiveShowSingleApplicationDialog();

private: // '_connectBackendToSignals()' for reflection
    void singleApp_connectBackendToSignals(){
        connect(
            back_con,&BackendConnectionSide::sendShowSingleApplication,
            this,&FrontendConnectionSide::receiveShowSingleApplicationDialog,
            Qt::QueuedConnection); 
    }