#!/bin/sh
# UTF8
# atgroup09@gmail.com
# 2019-2020


# Minimize single file (js, css)

# Example
#> minimize-file.sh file

CmpJar="yuicompressor-2.4.8.jar"

if [ -f $CmpJar ]; then
    if [ -f $1 ]; then

	DirName=$(dirname "$1")
	FileName=$(basename -- "$1")
	FileExt="${FileName##*.}"
	FileName="${FileName%.*}"
	FileOut=$DirName/$FileName.min.$FileExt

	if [ -f $FileOut ]; then
	    rm -f $FileOut
	fi
	
	java -jar $CmpJar $1 -o $FileOut
	
	if [ -f $FileOut ]; then
	    echo "+ $FileOut"
	fi
    fi
fi
