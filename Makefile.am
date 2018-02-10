# We don't fallow GNU file setup (no README, no AUTHOR, etc.)
AUTOMAKE_OPTIONS = foreign
SUBDIRS = src

dist_doc_DATA = README

README: README.md
        fgrep -v "[Build Status]" $< \
                | markdown \
                | html2text -style pretty -nobs \
                | sed -e 's:&gt;:>:g' \
                > $@.tmp
