@echo off
cd build
IF %1==1 ( cd debug ) ELSE IF %1==2 ( cd release ) ELSE ( echo incorrect input. type 1 for debug or 2 for release )
IF %1==1 ( main.exe ) ELSE IF %1==2 ( main.exe )