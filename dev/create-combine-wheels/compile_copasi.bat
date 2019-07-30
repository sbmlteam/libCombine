@echo off
SET BASE_DIR=%~dp0


:: compile archive
SET GENERATOR=Ninja
SET DEPENDENCY_DIR=E:\Development\copasi-dependencies
SET SWIG=c:\swigwin-3.0.12\swig.exe
SET CMAKE_ARGS=-DCMAKE_BUILD_TYPE=Release -DWITH_STATIC_RUNTIME=ON -DWITH_PYTHON=ON 
:: x86
call vs16
mkdir ninja_x86
pushd ninja_x86
set DEPENDENCY_32=%DEPENDENCY_DIR%\vs15_x86_static_bin
SET PYTHON_LIB=C:\Anaconda2_32\libs\python27.lib
SET PYTHON_INC=C:\Anaconda2_32\include
SET PYTHON=C:\Anaconda2_32\python
SET PYTHON_ARGS=-DPYTHON_EXECUTABLE=%PYTHON% -DPYTHON_INCLUDE_DIR=%PYTHON_INC% -DPYTHON_LIBRARY=%PYTHON_LIB% 
cmake -G %GENERATOR% %CMAKE_ARGS% %PYTHON_ARGS% -DCOMBINE_DEPENDENCY_DIR=%DEPENDENCY_32% -DSWIG_EXECUTABLE="%SWIG%" -DCOPASI_INSTALL_C_API=ON  -DCMAKE_INSTALL_PREFIX=../install_x86 ../src
cmake --build . --config Release --target binding_python_lib
ninja install
popd


:: x64
call vs16 x64
mkdir ninja_x64
pushd ninja_x64
set DEPENDENCY_64=%DEPENDENCY_DIR%\vs15_x64_Release_static_bin
SET PYTHON_LIB=C:\Anaconda2_64\libs\python27.lib
SET PYTHON_INC=C:\Anaconda2_64\include
SET PYTHON=C:\Anaconda2_64\python
SET PYTHON_ARGS=-DPYTHON_EXECUTABLE=%PYTHON% -DPYTHON_INCLUDE_DIR=%PYTHON_INC% -DPYTHON_LIBRARY=%PYTHON_LIB% 
cmake -G %GENERATOR% %CMAKE_ARGS% %PYTHON_ARGS% -DCOMBINE_DEPENDENCY_DIR=%DEPENDENCY_64% -DSWIG_EXECUTABLE="%SWIG%" -DCOPASI_INSTALL_C_API=ON -DCMAKE_INSTALL_PREFIX=../install_x64 ../src
cmake --build . --config Release --target binding_python_lib
ninja install
popd
