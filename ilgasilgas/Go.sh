#!/bin/bash

if [ "$USER" = "mykol" ]; then
    make
else
    # fakultetinis ar kitoks PC
    PATH="/usr/local/gcc/bin:$PATH"
    make
fi

./test.exe > test.txt
echo Testo rezultatai įrašyti į test.txt
