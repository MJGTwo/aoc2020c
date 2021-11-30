#!/bin.bash
do
    NAME=${FILE#"./"}
    NAME=${NAME%".txt"}
    echo $NAME
    strliteral --ident input $FILE $NAME.h
done