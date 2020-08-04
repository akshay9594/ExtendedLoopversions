# miniMD_ref-loops
Subscripted subscript loops in miniMD (The Mantevo Project) with function inlining.

1. The loop to be parallelized has been taken from subroutine 'sort' in atom.cpp 
2. Loops that fill and modify the subscript array are present in subroutine 'binatoms' in neighbor.cpp

The code is only a representative code showing the inlined version of the loops in question.
