	#!/bin/bash

if  [[ "$1" == "-v" ]]
then
    ifminusv=true
    programName="$2"
    directory="$3"
    parameter="-v"
else
    ifminusv=false
    programName="$1"
    directory="$2"
    parameter=""
fi

for i in "$directory/"*".in"
do
    baseName="`basename --suffix=.in "$i"`"
    inName="$directory/$baseName"
    ./"$programName" $parameter < "$inName.in" > "$inName.out2" 2> "$inName.err2"
    if ! diff "$inName.out" "$inName.out2" >/dev/null \
	|| { [[ "$ifminusv" == true ]] &&  ! diff "$inName.err" "$inName.err2" >/dev/null; }
    then
        echo "WRONG_ANSWER $i"
    else
        echo "OK $i"
    fi
    rm "$inName.out2"
    rm "$inName.err2"
done

