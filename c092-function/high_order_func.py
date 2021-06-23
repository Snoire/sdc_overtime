#! /usr/bin/env python3
# https://wizardforcel.gitbooks.io/sicp-py/content/1.6.html

def summation(n, term, next):
    total, k = 0, 1
    while k <= n:
        total, k = total + term(k), next(k)
    return total


def cube(k):
    return pow(k, 3)
def successor(k):
    return k + 1
def sum_cubes(n):
    return summation(n, cube, successor)

print(sum_cubes(3))



def identity(k):
    return k
def sum_naturals(n):
    return summation(n, identity, successor)

print(sum_naturals(10))
