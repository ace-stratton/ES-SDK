@echo off
SET GEN_PATH=..\..\..\lib\libhsm\hsmgen
python %GEN_PATH%\hsmgen.py --conf sxband_sched_sm.yaml --outpath . --templatepath %GEN_PATH%
