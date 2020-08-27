#!/bin/bash

function open_f() {
    FILE=$@
    if [[ $FILE == "" ]]; then
        echo "NO FILE"
        return -1
    fi
    if ( test -f "$FILE" ); then
        return 1
    fi
    touch $FILE
    return 0
}