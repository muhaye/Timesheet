# Our binary is produce here
bin_PROGRAMS = timesheet 
timesheet_SOURCES = main.c \
			   day_parse.c \
		   	   last_day.c \
			   nlist.c \
			   print_table.c \
			   read_rc_file.c \
			   init.c \
		   	   pdf_printer.c \
		   	   read_README.c \
		   	   timesheet.c

# main binary will be installed in the default directory for the "bin"s (hence we used the
# bin prefix.
# main_LDADD = pdflib.la  -L/usr/local/lib/ -lhpdf -Ilibharu/include
# libharu_a_LDADD = -L/usr/local/lib/ -lhpdf 
#jlibfoo_a_LDFLAGS = -Ilibharu/include 
timesheet_LDADD = -L/usr/local/lib/ -lhpdf 
# timesheet_LDADD = libhpdf.a 
# noinst_LIBRARIES = libhpdf.a
