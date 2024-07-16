@echo off
SET GEN_PATH=..\..\libhsm\hsmgen
rem python %GEN_PATH%\hsmgen.py --conf telemetry_sm.yaml --outpath . --templatepath %GEN_PATH%
python %GEN_PATH%\hsmgen.py --conf adcs_mode_sm.yaml --outpath . --templatepath %GEN_PATH%