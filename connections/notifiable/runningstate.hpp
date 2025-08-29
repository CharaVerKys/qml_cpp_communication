public:
    Q_PROPERTY(bool notifiable_appRunningState READ getAppRunningState WRITE setAppRunningState NOTIFY sendAppRunningStateChanged)

    void setAppRunningState(bool appRunningState){
        if (notifiable_appRunningState == appRunningState) {return;}
        notifiable_appRunningState = appRunningState;
        emit sendAppRunningStateChanged(notifiable_appRunningState);
    }
    bool getAppRunningState() const{ return notifiable_appRunningState; }

private:
    bool notifiable_appRunningState = false;

signals:
    void sendAppRunningStateChanged(const bool);

private: struct backendemit_runningstate{
    void receiveAppRunningStateChanged(const bool);
};

private: // '_connectNotifiableToBackend()' for reflection
    void runningState_connectNotifiableToBackend(){
        connect( this, &FrontendConnectionSide::sendAppRunningStateChanged,
            back_con,&BackendConnectionSide::receiveAppRunningStateChanged,
            Qt::QueuedConnection); 
    }