@echo off
SET GEN_PATH=..\..\..\..\lib\libhsm\hsmgen

python %GEN_PATH%\hsmgen.py --conf cubeadcs_gen2.yaml --outpath ..\gen\ --templatepath %GEN_PATH%