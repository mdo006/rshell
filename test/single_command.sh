#!/bin/sh
cd ..
cd src #enter src folder b/c that's where my program is
echo echo hello | ./a.out #echo "echo hello" to my file and runs it
echo ls -a | ./a.out
echo mkdir cs100 | ./a.out
echo git status | ./a.out
echo echo world | ./a.out
echo ls | ./a.out
echo date | ./a.out
#invalid inputs
echo ech hello | ./a.out
echo dat | ./a.out
echo lss -a | ./a.out
echo git hi | ./a.out
echo makedir testing | ./a.out