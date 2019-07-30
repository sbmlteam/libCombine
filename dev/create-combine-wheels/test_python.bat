@echo off
SET BASE_DIR=%~dp0

SET ANA_32=c:\Anaconda2_32\envs
SET ANA_64=c:\Anaconda2_64\envs

SET OLD_PATH=%PYTHONPATH%


SET PYTHONPATH=tmp-python\build\lib.win32-2.7;%ANA_32%\Library\bin;"%OLD_PATH%"
%ANA_32%\py27\python -c "import libcombine; import sys; print('libCombine ' + libcombine.getLibCombineDottedVersion() + ' running on: %%d.%%d.%%d' %% sys.version_info[:3]);"
SET PYTHONPATH=tmp-python\build\lib.win32-3.3;%ANA_32%\Library\bin;"%OLD_PATH%"
%ANA_32%\py33\python -c "import libcombine; import sys; print('libCombine ' + libcombine.getLibCombineDottedVersion() + ' running on: %%d.%%d.%%d' %% sys.version_info[:3]);"
SET PYTHONPATH=tmp-python\build\lib.win32-3.4;%ANA_32%\Library\bin;"%OLD_PATH%"
%ANA_32%\py34\python -c "import libcombine; import sys; print('libCombine ' + libcombine.getLibCombineDottedVersion() + ' running on: %%d.%%d.%%d' %% sys.version_info[:3]);"
SET PYTHONPATH=tmp-python\build\lib.win32-3.5;%ANA_32%\Library\bin;"%OLD_PATH%"
%ANA_32%\py35\python -c "import libcombine; import sys; print('libCombine ' + libcombine.getLibCombineDottedVersion() + ' running on: %%d.%%d.%%d' %% sys.version_info[:3]);"
SET PYTHONPATH=tmp-python\build\lib.win32-3.6;%ANA_32%\Library\bin;"%OLD_PATH%"
%ANA_32%\py36\python -c "import libcombine; import sys; print('libCombine ' + libcombine.getLibCombineDottedVersion() + ' running on: %%d.%%d.%%d' %% sys.version_info[:3]);"
SET PYTHONPATH=tmp-python\build\lib.win32-3.7;%ANA_32%\Library\bin;"%OLD_PATH%"
%ANA_32%\py37\python -c "import libcombine; import sys; print('libCombine ' + libcombine.getLibCombineDottedVersion() + ' running on: %%d.%%d.%%d' %% sys.version_info[:3]);"


SET PYTHONPATH=tmp-python\build\lib.win-amd64-2.7;%ANA_64%\Library\bin;"%OLD_PATH%"
%ANA_64%\py27\python -c "import libcombine; import sys; print('libCombine ' + libcombine.getLibCombineDottedVersion() + ' running on: %%d.%%d.%%d' %% sys.version_info[:3]);"
SET PYTHONPATH=tmp-python\build\lib.win-amd64-3.3;%ANA_64%\Library\bin;"%OLD_PATH%"
%ANA_64%\py33\python -c "import libcombine; import sys; print('libCombine ' + libcombine.getLibCombineDottedVersion() + ' running on: %%d.%%d.%%d' %% sys.version_info[:3]);"
SET PYTHONPATH=tmp-python\build\lib.win-amd64-3.4;%ANA_64%\Library\bin;"%OLD_PATH%"
%ANA_64%\py34\python -c "import libcombine; import sys; print('libCombine ' + libcombine.getLibCombineDottedVersion() + ' running on: %%d.%%d.%%d' %% sys.version_info[:3]);"
SET PYTHONPATH=tmp-python\build\lib.win-amd64-3.5;%ANA_64%\Library\bin;"%OLD_PATH%"
%ANA_64%\py35\python -c "import libcombine; import sys; print('libCombine ' + libcombine.getLibCombineDottedVersion() + ' running on: %%d.%%d.%%d' %% sys.version_info[:3]);"
SET PYTHONPATH=tmp-python\build\lib.win-amd64-3.6;%ANA_64%\Library\bin;"%OLD_PATH%"
%ANA_64%\py36\python -c "import libcombine; import sys; print('libCombine ' + libcombine.getLibCombineDottedVersion() + ' running on: %%d.%%d.%%d' %% sys.version_info[:3]);"
SET PYTHONPATH=tmp-python\build\lib.win-amd64-3.7;%ANA_64%\Library\bin;"%OLD_PATH%"
%ANA_64%\py37\python -c "import libcombine; import sys; print('libCombine ' + libcombine.getLibCombineDottedVersion() + ' running on: %%d.%%d.%%d' %% sys.version_info[:3]);"


SET PYTHONPATH=%OLD_PATH%
