mkdir build -p &&
cd build &&
qmake ../src/opencc-gui.pro &&
make &&
lrelease ../src/opencc-gui.pro &&
mv ../l10n/*.qm .
