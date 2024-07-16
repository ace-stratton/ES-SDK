@echo off
SET GEN_PATH=..\..\..\lib\libhsm\hsmgen
python %GEN_PATH%\hsmgen.py --conf eps_ctrl_sm.yaml --outpath . --templatepath %GEN_PATH%
