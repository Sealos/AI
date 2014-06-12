#! /bin/sh
#
#  Converting text files from CR/LF to LF format.

echo "Converting files to Unix format..."

find . -type f "(" -name "*.py" ")" \
   -exec sh -c "echo {};
                mv {} _tmpfile;
                tr -d \\\r < _tmpfile > {};
                touch -r _tmpfile {};
                rm _tmpfile
                chmod +x {}" \;

echo "Done!"
