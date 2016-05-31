#!/bin/sh
cd ..
cd src #enter src folder b/c that's where my program is
echo echo "hello #world" | ./a.out 
echo "ls #-a" | ./a.out
echo "ls -a || echo hello #echo world" | ./a.out
echo 55439 poop | ./a.out #invalid input
echo "mkdir #melissa" | ./a.out
echo "git status #what's the status?" | ./a.out
echo echo "Hi my name is #melissa" | ./a.out
echo "mkdir cs100#hi" | ./a.out
echo "ls -a; echo CS100 && mkdir testing #ldkflaal" | ./a.out
echo "echo hello || echo world; ls #-a" | ./a.out
echo "lss -a #hi" | ./a.out
echo "#hi" | ./a.out
echo "(echo hello) #echo hello" | ./a.out
echo "(echo hello && echo world) #hi there" | ./a.out
echo "(echo hello || echo world) && (echo hello; echo world) #don't print me" | ./a.out
echo "(echo hello && (echo hello)) #this is a comment" | ./a.out
echo "(echo hello || (echo hello)) #echo hello" | ./a.out
echo "ls -a && (echo hello) #dkjflaw" | ./a.out
echo "date; (echo hello && echo world) && ls #-a" | ./a.out
echo "(ls -a && mkdir stuff) && echo hi #comment" | ./a.out
echo "(ls -a && mkdir stuff) #&& echo hi #comment" | ./a.out
echo "echo hello || (ls && echo world) #ugh" | ./a.out
echo "echo hello && (mkdir stuff || date); ls #-a" | ./a.out
echo "date #|| (echo hello && echo world)" | ./a.out
echo "(ls -a) #&& (mkdir stuff || echo hello)" | ./a.out
echo "(date && ls -a) #|| (echo hello && git status)" | ./a.out
echo "(echo hello || date) #&& (git status && ls)" | ./a.out
echo "ls -a #&& (echo hello; echo world)" | ./a.out
echo "date #|| (echo hello && echo world)" | ./a.out
echo "ls -a && (echo hello; echo world) #|| exit" | ./a.out
echo "echo hello && echo world; (ls -a || mkdir stuff) #comments" | ./a.out

