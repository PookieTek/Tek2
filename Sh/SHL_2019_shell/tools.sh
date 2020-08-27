#!/bin/bash

. ./help.sh
. ./query.sh
. ./update.sh
. ./open_f.sh

function parser() {
    for ((j=0; j <= $#; j++)); do
        case "${!j}" in
            "-h")
                display_help;;
            "-f")
                next=$((j+1))
                open_f ${!next};;
            "-j")
                echo "-j";;
            "create")
                argument=$(get_args $j $@)
                createdb $argument;;
            "insert")
                argument=$(get_args $j $@)
                insertdata $argument;;
            "describe")
                describetable $((j+1));;
            "select")
                argument=$(get_args $j $@)
                find $argument;;
        esac
    done
}

function get_args() {
    base=$(($1+2))
    for ((i=$base; i <= $#; i++)); do
        case "${!i}" in
            "-f" | "create" | "insert" | "describe" | "select")
                return 0;;
            *)
                echo "${!i}"
        esac
    done
}

function readfile() {
    content=""
    while read line; do
        echo -e $line
    done < $FILE
}

function listTable() {
    a=$(echo $(grep "data_*" $FILE))
    a=${a//data_/}
    a=${a//:[/}
    a=${a//\"/}
    echo $a
}

function getDesc() {
    return $1
}

function getData() {
    return $1
}

function getDataLine() {
    return $1
}