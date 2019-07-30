::@echo off
SET BASE_DIR=%~dp0

SET CONDA_BASE=c:\Anaconda2_32
::
::pushd %CONDA_BASE%


for %%v in (
  py27
  py33
  py34
  py35
  py36
  py37
) do (

call %CONDA_BASE%\scripts\activate %%v
call %CONDA_BASE%\Scripts\conda install -y conda-build --prefix %CONDA_BASE%\envs\%%v
call %CONDA_BASE%\Scripts\conda update -y --prefix %CONDA_BASE%\envs\%%v --all
call %CONDA_BASE%\scripts\deactivate

)


SET CONDA_BASE=c:\Anaconda2_64

for %%v in (
  py27
  py33
  py34
  py35
  py36
  py37
) do (

call %CONDA_BASE%\scripts\activate %%v
call %CONDA_BASE%\Scripts\conda install -y conda-build --prefix %CONDA_BASE%\envs\%%v
call %CONDA_BASE%\Scripts\conda update -y --prefix %CONDA_BASE%\envs\%%v --all
call %CONDA_BASE%\scripts\deactivate

)
