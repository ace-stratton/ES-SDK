@echo off
SET GEN_PATH=..\..\..\core\lib\libhsm\hsmgen

python %GEN_PATH%\hsmgen.py --conf conops.yaml --outpath ..\gen\ --templatepath %GEN_PATH%