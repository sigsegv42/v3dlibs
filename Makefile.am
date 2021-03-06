AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I .

SUBDIRS = \
src/vertical3d/3dtypes \
src/vertical3d/command \
src/vertical3d/image \
src/vertical3d/font \
src/vertical3d/input \
src/vertical3d/audio \
src/vertical3d/gl \
src/vertical3d/brep \
src/vertical3d/hookah \
src/vertical3d/gui \
src/vertical3d/core \
src/vertical3d/tests \
src/vertical3d/imagetool

# make sure the root version file gets installed
v3d_includedir=$(includedir)/vertical3d-$(VERTICAL3D_API_VERSION)/vertical3d
v3d_include_HEADERS= \
version.h

# install m4 files
aclocaldir = $(datadir)/aclocal
aclocal_DATA = \
boost.m4 \
vertical3d.m4

gcov_sources = $(unit_tests_SOURCES)

if GCOV_ENABLED
gcov-report.txt: gcov-clean
	$(QUIET_GEN)(rm -f $@; \
	echo -e "Test coverage for v3D:\n" >> $@; \
	total_covered=0; total_actual=0; \
	for file in $(filter %.cxx,$(gcov_sources)); do \
		gcov -o .libs/$${file/.c/.gcda} $$file > /dev/null; \
		if test -f $$file.gcov; then \
			actual=`grep -v ' -:' $$file.gcov | wc -l`; \
			uncovered=`grep '#####:' $$file.gcov | wc -l`; \
			covered=$$((actual - uncovered)); \
			total_covered=$$((total_covered + covered)); \
			total_actual=$$((total_actual + actual)); \
			echo -e "$$file:    \t$$covered / $$actual\t($$((($$covered * 100) / $$actual))%)"; \
		fi \
	done >> $@; \
	cd $(abs_srcdir); \
	echo -e "\nSource lines: $$total_actual\nCovered statements: $$total_covered\nTotal coverage: $$((($$total_covered * 100) / $$total_actual))%" >> $@)

gcov: gcov-report.txt
	@echo ""; cat gcov-report.txt
cov:
	@make gcov-report
gcov-report:
	@mkdir -p coverage
	@lcov --compat-libtool --directory . --capture --output-file coverage/app.info
	@lcov --extract coverage/app.info *v3dlibs/* --output-file coverage/local.info
	@genhtml -o coverage/ coverage/local.info 
gcov-reset:
	@rm -fr coverage
	@find . -name "*.gcda" -exec rm {} \;
	@lcov --directory . --zerocounters
gcov-clean:
	@find . -name "*.gcda" -o -name "*.gcov" -delete
clean-local:
	@make gcov-reset 
check:
	@make test
	@make cov
else
gcov-report.txt:
	@true
cov-reset:
	@true
gcov-clean:
	@true
cov:
	@echo "Code coverage not enabled"
gcov:
	@echo "Need to reconfigure with --enable-gcov"
endif	# GCOV_ENABLED


test:
	@sh ./run-unit-tests.sh


.PHONY: gcov gcov-clean gcov-report.txt
