#!/bin/bash

#. ./tools.sh

function createdb() {
    case $1 in
        "database")
            if ! [[ $FILE ]]; then
                exit 1
            fi
            echo "OK"
            echo -e "{\n}" > $FILE;;
        "table")
            if [[ $# > 1 ]]; then
                new_table $@
            else
                echo "Please, Specify the table name"
            fi;;
        *)
            echo "Please, Specify if you want to create a Database or a Table"
            exit 1;;
    esac
}

function insertdata() {
    if [[ $# < 2 ]]; then
        echo "Bad Arguments"
        exit 1
    fi
    list=$(listTable)
    if ! [[ $list == *"$1"* ]]; then
        echo "This table doesn't exist"
        exit 1
    fi
    IFS=', ' read -r -a data <<< $2
    #CHECK FIELD EXIST HERE
    line=$(grep -n "data_"$1 $FILE | head -n 1 | cut -d: -f1)
    #CHECK IF DATA ALREADY EXIST
    insert="{\n"
    for elem in "${!data[@]}"
    do
        IFS='=' read -r -a value <<< ${data[elem]}
        insert=$insert"\"${value[0]}\":\"${value[1]}\""
        if [[ $((elem+1)) > ${#col[@]} ]]; then
            insert=$insert",\n"
        else
            insert=$insert"\n"
        fi
    done
    insert=$insert"}"
    #FORMAT DATA AND INSERT AT CORRECT LINE
    sed -i "$((line+1)) i\ $insert" $FILE
    echo "OK"
}

function new_table() {
    list=$(listTable)
    if [[ $list == *"$2"* ]]; then
        echo "This table already exist."
        exit 0
    fi
    desc="desc_"$2
    data="data_"$2
    content=$(readfile)
    if [[ $# > 2 ]]; then
        IFS=', ' read -r -a col <<< $3
        descript="\"$desc\":[\n"
        for elem in "${!col[@]}"
        do
            descript=$descript"\"${col[elem]}\""
            if [[ $((elem+1)) < ${#col[@]} ]]; then
                descript=$descript",\n"
            else
                descript=$descript"\n"
            fi
        done
        descript=$descript"],\n \"$data\":[\n],\n"
        sed -i "\$i $descript" $FILE
    fi
    echo "OK"
}