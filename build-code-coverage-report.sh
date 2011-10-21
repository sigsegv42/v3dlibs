#!/bin/sh

# NOTE: in order to create code coverage reports, the project must be built with gcov enabled:
#
# ./configure --enable-gcov
#

if [ ! -f src/image/readers/readers ]
then
  cd src/image/readers
  ln -nsf . readers
  cd ../../../
fi

if [ ! -d src/image/writers/writers ]
then
  cd src/image/writers
  ln -nsf . writers
  cd ../../../
fi

make gcov-clean
make gcov-reset
make test
make cov

exit 0
 

