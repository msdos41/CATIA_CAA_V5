@echo off
setlocal enabledelayedexpansion
echo Starting search and delete.........
echo.

set bat_path=%~dp0
::获得当前bat所在路径
cd /d %bat_path%
::定义到当前bat所在路径
del *.pdb /s /q 
::删除pdb文件
del cnext.exe /s /q
::删除cnext
for /f "delims=" %%i in ('dir /s /b CATSysCtrlWNTN.ctrl') do (
	::del /f /q %%i
	::echo.>%%i 2>nul 
	::cd.>%%i >nul 2>nul
	type nul %%i >nul 2>nul
)
::寻找所有CATSysCtrlWNTN.ctrl，并清空所有内容

echo.
echo Delete complete. Press Any Key to Continue....
pause >nul