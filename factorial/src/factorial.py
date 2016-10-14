# -*- coding:utf8 -*-
import time

MOD = 1000000
S = 0
inputNum = raw_input('Please input a number:')

def factorial( n ):
    mul = n;
    if n == 1:
        mul = 1
        return mul
    else:
        mul *= factorial(n-1)
        return mul
time1 = time.time()
for i in range(1, int(inputNum)+1):
    S += factorial(i)
time2 = time.time()
print "%d" % (S % MOD)
print "Time used = %.5f" % float(time2 - time1)
