@echo off
SET BASE_DIR=%~dp0

SET ANA_64=c:\Anaconda2_64\envs
SET DEP_64=e:\Development\copasi-dependencies\vs15_x64_Release_static_bin
SET INST_64=%BASE_DIR%\install_x64

for %%v in (
  py27
  py33
  py34
  py35
  py36
  py37
) do (
  call tmp-python\buildPython64.bat %ANA_64%\%%v\python.exe %%v %DEP_64% %INST_64%
)


copy /y tmp-python\b64_py27\_libcombine.pyd tmp-python\build\lib.win-amd64-2.7\libcombine 
copy /y tmp-python\script\libcombine.py tmp-python\build\lib.win-amd64-2.7\libcombine\__init__.py 

copy /y tmp-python\b64_py33\_libcombine.pyd tmp-python\build\lib.win-amd64-3.3\libcombine
copy /y tmp-python\script\libcombine.py tmp-python\build\lib.win-amd64-3.3\libcombine\__init__.py 

copy /y tmp-python\b64_py34\_libcombine.pyd tmp-python\build\lib.win-amd64-3.4\libcombine
copy /y tmp-python\script\libcombine.py tmp-python\build\lib.win-amd64-3.4\libcombine\__init__.py 

copy /y tmp-python\b64_py35\_libcombine.pyd tmp-python\build\lib.win-amd64-3.5\libcombine
copy /y tmp-python\script\libcombine.py tmp-python\build\lib.win-amd64-3.5\libcombine\__init__.py 

copy /y tmp-python\b64_py36\_libcombine.pyd tmp-python\build\lib.win-amd64-3.6\libcombine
copy /y tmp-python\script\libcombine.py tmp-python\build\lib.win-amd64-3.6\libcombine\__init__.py 

copy /y tmp-python\b64_py37\_libcombine.pyd tmp-python\build\lib.win-amd64-3.7\libcombine
copy /y tmp-python\script\libcombine.py tmp-python\build\lib.win-amd64-3.7\libcombine\__init__.py 


SET OLD_PATH=%PATH%

for %%v in (
  py27
  py33
  py34
  py35
  py36
  py37
) do (

  pushd tmp-python
  %ANA_64%\%%v\python.exe setup.py bdist_wheel --skip-build
  
  SET PATH=%ANA_64%\%%v\;%ANA_64%\%%v\Library\bin;%ANA_64%\Library\bin;"%OLD_PATH%"
  %ANA_64%\%%v\python.exe setup.py bdist_conda --skip-build
  popd
)


SET PATH=%OLD_PATH%