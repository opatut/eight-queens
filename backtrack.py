#!/usr/bin/env python3

import traceback

class SolutionFound(Exception):
    pass

SIZE = 8
COUNT = 0
FIELD = [[False for x in range(SIZE)] for y in range(SIZE)]

def print_field():
    print("+" + "-" * SIZE + "+")
    for x in FIELD:
        print("|", end="")
        for y in x:
            print("X" if y else " ", end="")
        print("|")
    print("+" + "-" * SIZE + "+")

def next():
    for i in range(SIZE):
        if valid_row(i):
            for j in range(SIZE):
                if valid_col(j):
                    if valid_diag(i, j):
                        select(i, j)

def select(x, y):
    global FIELD, COUNT
    FIELD[x][y] = True
    COUNT += 1
    if COUNT >= SIZE:
        raise SolutionFound()
    next()
    FIELD[x][y] = False
    COUNT -= 1

def valid_row(x):
    global FIELD
    for i in range(SIZE):
        if FIELD[x][i]:
            return False
    return True

def valid_col(y):
    global FIELD
    for i in range(SIZE):
        if FIELD[i][y]:
            return False
    return True

def valid_diag(x, y):
    global FIELD
    for i in range(-SIZE+1, SIZE):
        if y+i<0 or y+i >= SIZE: continue
        # diag1
        if x+i<SIZE and x+i>=0 and FIELD[x+i][y+i]: return False
        if x-i<SIZE and x-i>=0 and FIELD[x-i][y+i]: return False
    return True

try:
    next()
except SolutionFound:
    #traceback.print_exc()
    print_field()
else:
    print("Nothing found.")
