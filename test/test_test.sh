#!/bin/sh
cd ..
cd src #enter src folder b/c that's where my program is
[]
[ ]
test
test -e tests                     #returns true 
test -e single_command.sh         #returns true 
test -e thei.cpp                  #returns false 

test -d tests                     #returns true
test -d single_command.sh         #returns false 
test -d thei.cpp                  #returns false 

test -f tests                     #returns false 
test -f single_command.sh         #returns true 
test -f thei.cpp                  #returns false 

test -e tests; mkdir tests && test tests

test tests                        #returns true and it will run as -e
test -g tests                     #returns false
[tests]                           #returns true


[ -e tests && echo "path exists" ]        #returns true and "path exists"  
[ -d tests && echo "path exists" ]        #returns true and "path exists"  
[ -f single_command.sh && echo "path exists" ]    #returns true and "path exists"  

[ -e tests || echo "path exists" ]        #returns true and "path exists"  
[ -d tests || echo "path exists" ]        #returns true and "path exists"  
[ -f single_command.sh && echo "path exists" ]    #returns true and "path exists"  

[testsrer] || test -e tests || test -f single_command.sh # returns false true
(test -f bin || echo hello) && (ls &&  ech || [ -d bin ] )

[/home/ubuntu/workspace/test/tests/]
[] && test /home/ubuntu/workspace/test/tests/ #returns false
[-e]
[-e tesvbt] || echo hello
ech hero && test -f /home/ubuntu/workspace/test/tests/
echo hello && test -f /home/ubuntu/workspace/test/tests/
([/home/ubuntu/workspace/test/tests/] && echo first) ||echo hi
[/home/ubuntu/workspace/test/tests/ wdv ]




