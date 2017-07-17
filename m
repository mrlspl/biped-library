make clean
autoreconf -if
./configure
make -j 8
sudo make install
make run-unit-tests
