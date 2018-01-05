# Install instructions

To install or develop the Solri version of Urbit, you need to build it
from source.

# Build instructions

[![Build Status](https://travis-ci.org/urbit/urbit.svg?branch=maint-0.4)](https://travis-ci.org/urbit/urbit)

## External dependencies

`vere`, the Urbit virtual machine, depends on the following:

- C compiler ([gcc](https://gcc.gnu.org) or [clang](http://clang.llvm.org))
- [GNU Make](https://www.gnu.org/software/make/)
- [GMP](https://gmplib.org)
- [CMake](https://cmake.org)
- automake, autoconf, and libtool
- [OpenSSL](https://www.openssl.org)
- [libsigsegv](https://www.gnu.org/software/libsigsegv/)
- [libcurl](https://curl.haxx.se/libcurl/)
- curses implementation (ncurses on Linux distributions, OS curses otherwise)
- [Ragel](https://www.colm.net/open-source/ragel/)
- [re2c](http://re2c.org)

Most of these dependencies are unfortunate; we aim to drastically shrink the
list in upcoming versions. `vere` proper makes use of GMP, OpenSSL, libcurl, and
libsigsegv. The multiple build tools are a result of bundled libraries, slated
for future unbundling or removal wherever possible.

## Building

Our Makefile should handle the build smoothly on all supported platforms. It's
just a simple Makefile, written by hand for GNU Make, and the most complicated
parts of its internal machinery have to do with the varied build systems of the
bundled libraries.

Useful targets are the default `all`, `clean`, and `distclean`. The last may not
produce an entirely clean distribution directory, and runs a bundled library's
configure script; `git clean` may be a better option.

The `vere` binary is produced in `bin/urbit`.

## Building the Debian Package

To build a .deb file for installation on Debian platforms, perform the
following steps:
+ Run `sudo apt install devscripts` to install the `debuild` utility.
+ Update the `debian/changelog` to reflect the changes in this release.
+ If necessary, update the year of the copyright in `debian/copyright`.
+ Clean any build artifacts: Run `make clean` and delete the `bin` directory,
if it exists.
+ Run `tar -xcvf ../urbit-x.y.z.orig.tar.gz .` from the top-level folder in
the repo.  This command will create an archive in the directory above the
current directory, which will be used in packaging.
+ Run `debuild -us -uc`, also from the top-level folder in the repo. This
creates a .deb file in the folder above the current directory.

The resulting .deb file should now exist in the folder above the current
directory. To test that the .deb file works properly, you can perform the
following steps:
+ Uninstall urbit: `sudo apt remove urbit`.
+ Run `sudo dpkg -i ../urbit-x.y.z_amd64.deb` to install the new version.
+ Boot up a ship using the `urbit` command.

## Contact

If you have any questions, problems, patches, or proposals for patches, please
feel free to get in touch in whatever way is most convenient:

- Create an issue on this repository.
- Find me on [~zod](https://zod.that.world) or email me directly
  [hi@that.world](mailto:hi@that.world).
