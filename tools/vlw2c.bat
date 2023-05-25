@echo off
bin2hex --i %1\FontFiles\%2.vlw --o %3.c

echo #include ^<Arduino.h^> > ..\src\fonts\%3.h
echo. >>  ..\src\fonts\%3.h
echo #ifndef %3_H >>  ..\src\fonts\%3.h
echo #define %3_H 1 >>  ..\src\fonts\%3.h
echo const uint8_t %3[] PROGMEM = >>  ..\src\fonts\%3.h
echo { >>  ..\src\fonts\%3.h
type %3.c >> ..\src\fonts\%3.h
echo } >> ..\src\fonts\%3.h
echo ; >> ..\src\fonts\%3.h
echo. >>  ..\src\fonts\%3.h
echo #endif >>  ..\src\fonts\%3.h
del %3.c