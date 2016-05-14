#!/bin/sh
cd ..
cd src #enter src folder b/c that's where my program is
echo exit | ./a.out
echo ls -a || exit | ./a.out #should NOT exit
echo echo hello && exit | ./a.out
echo ech hello && exit | ./a.out #should NOT exit
echo ls -a || echo hi && exit | ./a.out
echo echo Melissa && echo Judy || exit ./a.out
echo echo Melissa && echo Judy && exit ./a.out
echo mkdir test || exit | ./a.out
echo mkdir test && exit | ./a.out
echo ls -a && eho melissa || exit