@echo off
SET BASE_DIR=%~dp0

if exist tmp-python\dist (

copy /y tmp-python\dist\*.whl out

)

if exist src rd /s /q src
if exist tmp-python rd /s /q tmp-python
if exist install_x86 rd /s /q install_x86
if exist install_x64 rd /s /q install_x64
if exist ninja_x64 rd /s /q ninja_x64
if exist ninja_x86 rd /s /q ninja_x86
