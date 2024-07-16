@echo off
rem set mypath=%~dp0
set mypath=C:\Install

setlocal
set GRAPHVIZ_DOT=%mypath%\Graphviz\bin\dot.exe

java %PLANTUML_JAVAOPTS% -jar %mypath%\plantuml.jar %*