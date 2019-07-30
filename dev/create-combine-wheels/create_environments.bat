::@echo off
SET BASE_DIR=%~dp0

::SET CONDA_BASE=c:\anaconda_32
::
::pushd %CONDA_BASE%

call conda create -y -n py27 python=2.7
call conda create -y -n py33 python=3.3
call conda create -y -n py34 python=3.4
call conda create -y -n py35 python=3.5
call conda create -y -n py36 python=3.6
call conda create -y -n py37 python=3.7

