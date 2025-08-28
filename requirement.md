# List of requirement for launcher app
1. Single application logic
2. Catch core dump and send to provided mail {settings, all logs, core dump file *(if exist)*, crashLog.txt, application version}
3. kill -SIGUSR1 on application when got positive on one-directional pipe
4. Restart application after crash if required to
    * ~~if restart frequency greater than build-in timeout and happened more than 5 times, stop restarting and lock modbus (if specified) on error~~
5. ability to change of settings, that runtime constants in application (from build-in list)