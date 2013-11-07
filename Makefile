PROJECT=42sh
VERSION=1.0
USER=maarek_j
TARBALL=${USER}-${PROJECT}-${VERSION}
BIN=42sh

all:
	make -C build
	cp -vf build/*.a lib/
	cp -vf build/${BIN} .

clean: checkclean
	make -C build clean
	rm -fv lib/*.so lib/*.a
	rm -fv ${BIN}

cleandoc:
	rm -Rfv doc/html doc/latex

checkclean:
	cp test/build/CMakeLists.txt test/
	rm -fR test/build/*
	rm -fv test/main_test/*
	mv test/CMakeLists.txt test/build/
	rm -fv test/html/index.html


buildclean:
	cp build/CMakeLists.txt .
	rm -fR build/*
	mv CMakeLists.txt build/

distclean: clean cleandoc buildclean
	rm -fv src/42sh/config.h
	find . -type f -name "*~" -exec rm -rfv {} \;
	find . -type f -name "*.swp" -exec rm -rfv {} \;
	find . -type f -name "~*" -exec rm -rfv {} \;
	find . -type f -name "\#*" -exec rm -rfv {} \;
	rm -vf ${TARBALL}.tar.bz2
	rm -Rvf ${TARBALL}
	find . -type f -name "*~" -exec rm -rfv {} \;

dist: distclean
	mkdir ${TARBALL}
	cp -Rvf `ls | grep -v ${TARBALL}` ${TARBALL}
	tar --exclude='.*' -cvjf ${TARBALL}.tar.bz2 ${TARBALL}
	chmod 640 ${TARBALL}.tar.bz2
	rm -Rf ${TARBALL}

distcheck: dist
	tar -xvjf ${TARBALL}.tar.bz2 ${TARBALL}
	cd ${TARBALL}
	./configure && make check

doc: cleandoc
	doxygen doc/doxyfile.conf
	make -C doc/latex

checkbuild: all
	export CFLAGS="-std=c99";
	(cd test/build ; cmake -G"Unix Makefiles" ; cd ../..);
	make -C test/build

checkhtml: check
	(cd test; firefox html/index.html);

check: checkbuild
	(cd test; perl Moulinette.pl);

norme:
	grep -nE ".{79}" ${SRC_DIR}*.c ${INCLUDE_DIR}*.h ; echo -n
	grep -nE "[^ ] +;" ${SRC_DIR}*.c ${INCLUDE_DIR}*.h ; echo -n
	grep -nE " $" ${SRC_DIR}*.c ${INCLUDE_DIR}*.h ; echo -n

.PHONY: check
