#!/bin/sh
cd ..
cd src #enter src folder b/c that's where my program is
echo (echo hello) | ./a.out
echo (echo hello || (echo hello)) | ./a.out
echo (echo hello && echo world) | ./a.out
echo (echo hello; echo world) | ./a.out
echo exit && (echo hello || echo world) | ./a.out
echo (echo hello && echo hello) && (echo hello && echo hello) | ./a.out
echo (ls && echo hello) || (echo hello && echo hello) | ./a.out
echo (echo hello && echo hello); (echo hello && echo hello) | ./a.out
echo (echo hello && (echo hello && (echo hello))) | ./a.out
echo (echo hello || echo hello) | ./a.out
echo (echo hello && (ls -a)) | ./a.out
echo (echo hello || echo hello) && echo hello | ./a.out
echo (echo hello || mkdir stuff) || echo hello | ./a.out
echo (echo hello) && (echo world) | ./a.out
echo (echo hello) || (echo world) | ./a.out
echo (echo hello); (echo world) | ./a.out
echo (echo hello) && (echo hello) || (echo hello); (echo hello) | ./a.out
echo (ech hello && date) && echo hello | ./a.out
echo (ech hello && echo hello) || echo hello | ./a.out
echo (ech hello && echo hello); echo hello | ./a.out
echo (echo hello && ech hello) && echo hello | ./a.out
echo (echo hello && ech hello) || echo hello | ./a.out
echo (echo hello && ech hello); echo hello | ./a.out
echo (echo hello && echo hello); ech hello | ./a.out
echo (ls -a && ls) | ./a.out
echo (ls -a) && (mkdir stuff || echo hello) | ./a.out
echo (date && ls -a) || (echo hello && git status) | ./a.out
echo (echo hello || date) && (git status && ls) | ./a.out
echo ls -a && (echo hello; echo world) | ./a.out
echo date || (echo hello && echo world) | ./a.out
echo date; (echo hello || echo world) | ./a.out
echo ls -a && (echo hello; echo world) || exit | ./a.out