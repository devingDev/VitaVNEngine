rm -rf build/
mkdir build
cd build
cmake ..
make -j4

mv VVNE.vpk VVNE.zip
7z a VVNE.zip ../assets
mv VVNE.zip VVNE.vpk

echo "DONE"
echo ""
