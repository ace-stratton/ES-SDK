@echo off
SET GEN_PATH=..\..\..\Infrastructure\libhsm\hsmgen
python %GEN_PATH%\hsmgen.py --conf beacons_sm.yaml --outpath . --templatepath %GEN_PATH%