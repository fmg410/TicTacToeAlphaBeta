@ECHO OFF
cd build
g++ -g ..\*.cpp -o app.exe -O2 -ID:\SFML-2.5.1\include -LD:\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
.\app.exe