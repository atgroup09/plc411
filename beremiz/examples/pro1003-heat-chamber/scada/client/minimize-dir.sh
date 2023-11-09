#!/bin/sh
# UTF8
# atgroup09@gmail.com
# 2019-2020


# Minimize files in directory

# Example:
#> minimize-dir.sh dir

Exec="minimize-file.sh"
Files="main.js main.css debug.js form-v2.js hmi-v2-main.js hmi-v2.js log.js popup-dialog.js popup-form.js response-result.js ui-engine.js ui-func.js ui-hmi-v2.js ui-hmi-v2.css bit.js date.format.js"

if [ -f $Exec ]; then
    if [ -d $1 ]; then
	for f in $Files
	do
	    $Exec $1/$f
	done
    fi
fi
