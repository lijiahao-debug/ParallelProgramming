#!/bin/bash
name=`echo $1 | cut -d \. -f 1`
ss=`echo $1 | cut -d \. -f 2`

if [ ss='c' ];
    then
        command `mpincc $1 -o ../build/${name}`
    elif [ ss='cpp' ]
    then
        command `mpinc++ $1 -o ${name}`
fi
rm ${name}.o

