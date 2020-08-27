#!/bin/bash

function describetable() {
    echo "Describe function" $@
}

function find() {
    list=$(listTable)
    if ! [[ $list == *"$1"* ]]; then
        echo "This table doesn't exist"
        exit 1
    fi
}