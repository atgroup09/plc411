#!/bin/sh
# UTF8
# atgroup09@gmail.com
# 2019-2020

# Minimize source-files of the project

# Example
#> production.sh start         - minimize
#> production.sh start release - minimize and remove source-files


Exec="minimize-file.sh"
Projects="mod lib/js pro-ud1a pro-ud1a/boil pro-bh50 pro-bh50/boil"
Files="main.js main.css debug.js form-v2.js hmi-v2-main.js hmi-v2.js log.js popup-dialog.js popup-form.js response-result.js ui-engine.js ui-func.js ui-hmi-v2.js ui-hmi-v2.css bit.js date.format.js"

if [ "$1" = "start" ]; then
    if [ -f $Exec ]; then
	for p in $Projects
	do
	    for f in $Files
	    do
		if [ -f $p/$f ]; then
		    $Exec $p/$f
		
		    if [ "$2" = "release" ]; then
			rm -f $p/$f
		    fi
		
		    if [ ! -f $p/$f ]; then
			echo "- $p/$f"
		    fi
		fi
	    done
	done
    fi
fi
