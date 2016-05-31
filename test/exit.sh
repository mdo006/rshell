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
echo ls -a && eho melissa || exit | ./a.out
echo (echo hello); exit | ./a.out
echo (echo hello && echo world) && exit | ./a.out
echo (echo hello && echo world) || exit | ./a.out
echo exit && (echo hello || echo world) | ./a.out
echo (echo hello && echo hello) && (echo hello && echo hello) || exit | ./a.out
echo (echo hello && echo hello) && (echo hello && echo hello) && exit | ./a.out
echo (echo hello && echo hello) && (echo hello && echo hello); exit | ./a.out
echo (ls -a && date) && exit | ./a.out
echo (mkdir stuff; echo hello) || (ls -a; exit) | ./a.out
echo (mkdir stuff; echo hello) && (ls -a; exit) | ./a.out
echo (mkdir stuff; echo hello); (ls -a; exit) | ./a.out
echo (ls -a && ls) && exit | ./a.out
echo (ls -a) && (mkdir stuff || echo hello); exit | ./a.out
echo (date && ls -a) || (echo hello && git status); exit | ./a.out
echo (echo hello || date) && (git status && ls) && exit | ./a.out
echo ls -a && (echo hello; echo world) || exit | ./a.out
echo date || (echo hello && echo world); exit | ./a.out
echo date; (echo hello || echo world) && exit | ./a.out
echo ls -a && (echo hello; echo world) || exit | ./a.out
echo (ls -a && exit) | ./a.out
echo (mkdir stuff || exit) | ./a.out
echo (echo hello; exit) | ./a.out