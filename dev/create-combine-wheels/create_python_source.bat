@echo off
SET BASE_DIR=%~dp0

cmake -P create_python_source.cmake %*
