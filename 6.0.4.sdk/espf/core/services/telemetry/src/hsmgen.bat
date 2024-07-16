@echo off
SET GEN_PATH=..\..\..\lib\libhsm\hsmgen
rem python %GEN_PATH%\hsmgen.py --conf telemetry_sm.yaml --outpath . --templatepath %GEN_PATH%
python %GEN_PATH%\hsmgen.py --conf telemetry_file_sink_sm.yaml --outpath . --templatepath %GEN_PATH%