#!/usr/bin/bash

JARNAME=macchiato/macchiato.jar
JAVAEXE=java

echo Running C generator...
$JAVAEXE -jar $JARNAME --gen-c ./config/deploy_all_default.fdepl

echo Running Python generator...
$JAVAEXE -jar $JARNAME --gen-py ./config/deploy_all_default.fdepl
echo Updating files in other/tests/fp_api...
cd src-gen-py
find . -name \*ClientApp.py -exec cp -v {} ../../../tests/fp_api \;
# '-quit' to stop after the first SerDesHelpers.py is found a copied.
find . -name SerDesHelpers.py -exec cp -v {} ../../../tests/fp_api \; -quit
cd ..

echo Running JS generator...
$JAVAEXE -jar $JARNAME --gen-js ./config/deploy_all_default.fdepl

echo Running DC generator...
$JAVAEXE -jar $JARNAME --gen-dc ./config/deploy_dc.fdepl

echo Copy the DC generation to the config datacache folder to generate the js and py code
cp -v src-gen-dc/data_cache/*/datacache.py ../../tests/fp_api

echo Running generators again to generate output for datacache_io interface...
$JAVAEXE -jar $JARNAME --gen-py ./config/deploy_dc_io.fdepl
$JAVAEXE -jar $JARNAME --gen-js ./config/deploy_dc_io.fdepl
