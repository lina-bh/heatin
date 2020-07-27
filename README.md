# heatin?

it's some kind of HWMonitor clone for linux. right now it only shows the sensor input data from lm-sensors. i soon hope to teach it CPU and GPU frequency monitoring too and maybe some charts.

you will need:

* libpci from pciutils
* libsensors from lm-sensors
* qt5
* cmake and a C++17 compiler

clone and download [libsensors-cpp](https://github.com/sfranzen/libsensors-cpp):

```
$ git clone https://gitlab.com/flatulation/heatin.git
$ cd heatin
$ git submodule update --init
```

build:

```sh
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make # in parallel use -j and your number of cores plus one
```

install from build dir:

```
# make install
```

alternatively use cmake's amazing build capabilities:

```
$ cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
$ cmake --build build/ --parallel
$ cmake --install build
```

## Licence

heatin - hardware monitoring program for linux

Copyright © 2020 Lina Bane (flatulation)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is not a program of honour.

No highly esteemed function is executed here... no values are evaluated.

What is here is dangerous and repulsive to us.

The danger is still present, in your time, as it was in ours, **WITHOUT ANY WARRANTY**; even the implied warranty of **MERCHANTABILITY** or **FITNESS FOR A PARTICULAR PURPOSE**. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.

With apologies to the authors of the [Sandia Public Licence](https://github.com/cdanis/sandia-public-license).