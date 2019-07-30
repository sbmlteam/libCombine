@echo off
SET BASE_DIR=%~dp0

SET ANA_32=c:\Anaconda2_32\envs
SET DEP_32=e:\Development\copasi-dependencies\vs15_x86_static_bin
SET INST_32=%BASE_DIR%\install_x86

for %%v in (
  py27
  py33
  py34
  py35
  py36
  py37
) do (
  call tmp-python\buildPython32.bat %ANA_32%\%%v\python.exe %%v %DEP_32% %INST_32%
)

copy /y tmp-python\b32_py27\_libcombine.pyd tmp-python\build\lib.win32-2.7\libcombine 
copy /y tmp-python\script\libcombine.py tmp-python\build\lib.win32-2.7\libcombine\__init__.py 

copy /y tmp-python\b32_py33\_libcombine.pyd tmp-python\build\lib.win32-3.3\libcombine 
copy /y tmp-python\script\libcombine.py tmp-python\build\lib.win32-3.3\libcombine\__init__.py 

copy /y tmp-python\b32_py34\_libcombine.pyd tmp-python\build\lib.win32-3.4\libcombine 
copy /y tmp-python\script\libcombine.py tmp-python\build\lib.win32-3.4\libcombine\__init__.py 

copy /y tmp-python\b32_py35\_libcombine.pyd tmp-python\build\lib.win32-3.5\libcombine 
copy /y tmp-python\script\libcombine.py tmp-python\build\lib.win32-3.5\libcombine\__init__.py 

copy /y tmp-python\b32_py36\_libcombine.pyd tmp-python\build\lib.win32-3.6\libcombine 
copy /y tmp-python\script\libcombine.py tmp-python\build\lib.win32-3.6\libcombine\__init__.py 

copy /y tmp-python\b32_py37\_libcombine.pyd tmp-python\build\lib.win32-3.7\libcombine 
copy /y tmp-python\script\libcombine.py tmp-python\build\lib.win32-3.7\libcombine\__init__.py 


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
  %ANA_32%\%%v\python.exe setup.py bdist_wheel --skip-build
  
  SET PATH=%ANA_32%\%%v\;%ANA_32%\%%v\Library\bin;%ANA_32%\Library\bin;"%OLD_PATH%"
  ::%ANA_32%\%%v\python.exe setup.py bdist_conda --skip-build
  popd
)

SET PATH=%OLD_PATH%