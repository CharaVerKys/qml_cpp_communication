
// ! btw i actually not tested that this works,
// ! but if docs not mislead and signal works same way as all other,
// ! notifiable part is correct

    Q_PROPERTY(bool option_sendCrashReport READ getCrashReporting WRITE setCrashReporting NOTIFY sendCrashReportChanged)
public:
    void setCrashReporting(bool sendCrashReport){
        if (option_sendCrashReport == sendCrashReport) {return;}

        option_sendCrashReport = sendCrashReport;
        emit sendCrashReportChanged(option_sendCrashReport);
    }
    bool getCrashReporting() const{ return option_sendCrashReport; }

private:
    bool option_sendCrashReport;
signals:
    void sendCrashReportChanged(const bool);