public:
    Q_PROPERTY(bool option_sendCrashReport READ getCrashReporting WRITE setCrashReporting NOTIFY sendCrashReportChanged)
    void setCrashReporting(bool sendCrashReport){
        if (option_sendCrashReport == sendCrashReport) {return;}
        option_sendCrashReport = sendCrashReport;
        emit sendCrashReportChanged(option_sendCrashReport);
    }
    bool getCrashReporting() const{ return option_sendCrashReport; }

private:
    bool option_sendCrashReport = true;
signals:
    void sendCrashReportChanged(const bool);
private: struct backendemit_crashreport{
    void receiveCrashReportOptionChanged(const bool);
};

private: // '_connectNotifiableToBackend()' for reflection
    void crashReport_connectNotifiableToBackend(){
        connect( this, &FrontendConnectionSide::sendCrashReportChanged,
            back_con,&BackendConnectionSide::receiveCrashReportOptionChanged,
            Qt::QueuedConnection); 
    }