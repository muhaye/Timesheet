# Initialize AC: ACINIT( package_name, version, bug_report_address)
AC_INIT([timesheet], [0.1])
# Initialize Automake
AM_INIT_AUTOMAKE
# We use libraries
AC_PROG_RANLIB
# Let's check for a C compiler
AC_LANG(C)
# Let's set a C compiler
AC_PROG_CC
# Let's specify where the Makefiles should be produced
# There are the same location as your Makefile.in's, but named as Makefile only
# We need to do this because Autoconf and Automake read this file and
# produce Makefile from this list.
AC_CONFIG_FILES([Makefile src/Makefile])
# Finally produce "configure" script
AC_OUTPUT
