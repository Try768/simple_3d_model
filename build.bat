cl /c include\*.cpp /EHsc
lib tick.obj   



cl /EHsc /Iinclude main.cpp /link User32.lib ole32.lib kernel32.lib gdi32.lib *.lib /out:ngasu.exe 