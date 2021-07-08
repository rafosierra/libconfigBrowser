#!/bin/bash

## translate.sh
## updates translation sources (.ts files) and releases them (.qm files)

TSFILES="libconfigBrowser_ja.ts libconfigBrowser_en.ts"

# update translations:
# -no-recursive = Do not recursively scan directories.
# -no-obsolete = Drop all obsolete and vanished string
lupdate -no-recursive -no-obsolete . -ts $TSFILES

# release translations:
lrelease $TSFILES

