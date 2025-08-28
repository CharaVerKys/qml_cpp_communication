## qml_cpp_communication
my implementation of frontend-backend connection between qml and cpp context  
*using only qml context property*

### overall
if you want look at lacks of this strategy see:  
https://doc.qt.io/qt-6/qtqml-cppintegration-contextproperties.html  
---
meanwhile code itself is fine and works as expected  
works on clang  
feel free to contribute to connection system  

### extra
i not looked at qml singleton (as cpp object) because i got bored at reading documentation
**you also may prefer different name convention for signal_slots** *(there is like only 20 connections for me so i decide it would take too much effort for small improve, for now)*
*no ai involved in design or codding, except preprocessor.elf (changed manually because ai did it wrong)*
*not all project files provided, only connection relevant part*