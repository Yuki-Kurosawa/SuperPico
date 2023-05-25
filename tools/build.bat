@echo off
set PD=C:\processing-4.2\processing-java.exe
set DIR=%~dp0
%PD% --sketch=%DIR%\Create_font_en --run
call vlw2c.bat Create_font_en unifont16 unifont_en

%PD% --sketch=%DIR%\Create_font_cn --run
call vlw2c.bat Create_font_cn unifont16 unifont_cn

%PD% --sketch=%DIR%\Create_font_jp --run
call vlw2c.bat Create_font_jp unifont-jp16 unifont_jp

%PD% --sketch=%DIR%\Create_font_cjk --run
call vlw2c.bat Create_font_cjk unifont-jp16 unifont_cjk