#!/bin/sh

get_abs_filename() {
  # $1 : relative filename
  if [ -d "$(dirname "$1")" ]; then
    echo "$(cd "$(dirname "$1")" && pwd)/$(basename "$1")"
  fi
}

rm -r Binaries
rm -r DerivedDataCache
rm -r Intermediate
rm -r Plugins/*/Binaries
rm -r Plugins/*/Intermediate

uproject=$(get_abs_filename "TalosRecords.uproject")

echo "Generating source files..."
exec "$2" -projectfiles "${uproject}" & wait $!
echo "Recompiling... Make sure to rebuild missing modules!"
echo "Project will automatically open when compiling is done."
"$1" "${uproject}" &
exit 0