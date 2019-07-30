@echo off 

REM This file will build the python source dist 64 bit
REM
REM 2011/02/26 Frank Bergmann
REM

REM ensure visual studio is in the path
if "%INCLUDE%"=="" call vs16.bat x64

REM set up directory variables
SET THIS_DIR=%~dp0

REM check argument
SET PYTHON_INTERP=%1
if "%PYTHON_INTERP%" == "" goto MISSING_INTERP

SET VERSION=%2
if "%VERSION%" == "" SET VERSION=py27


SET DEP_DIR=%3
if "%DEP_DIR%" == "" SET DEP_DIR=../../../win64/

SET INST_DIR=%4
if "%INST_DIR%" == "" SET INST_DIR=../install_x64


REM create build dir
if not exist %THIS_DIR%\b64_%VERSION% mkdir %THIS_DIR%\b64_%VERSION%
pushd %THIS_DIR%\b64_%VERSION%
cmake -G "Ninja"  -DPYTHON_EXECUTABLE="%PYTHON_INTERP%" -DDEP_DIR="%DEP_DIR%" -DINST_DIR="%INST_DIR%" ..
ninja
popd

goto ALL_DONE

:MISSING_INTERP
echo.
echo Please provide the python interpreter to use as first argument.
echo. 
goto ALL_DONE

:ALL_DONE
cd  /d %BASE_DIR%
