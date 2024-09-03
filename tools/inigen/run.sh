#! /bin/bash
set -e # Don't replace the existing config it it's broken
echo "--- Compiling inigen app ---"
make
echo "--- Generating offsets ---"
./inigen ../../pokeemerald-speedchoice.elf emerald_ex_offsets.ini --code "SPDX" --name "Emerald EX (U)"
echo "--- Updating JAR ---"
mkdir -p ./com/dabomstew/pkrandom/config/
cp emerald_ex_offsets.ini ./com/dabomstew/pkrandom/config/emerald_ex_offsets.ini
jar uf UPR_EX.jar com/dabomstew/pkrandom/config/emerald_ex_offsets.ini
echo "Success - You can now run the jar!"