# miniMD-loops
Subscripted subscript loops in miniMD (The Mantevo Project) with function inlining.

1. The loop to be parallelized has been taken from subroutine 'sort' in atom.cpp 
2. Loops that fill and modify the subscript array are present in subroutine 'binatoms' in neighbor.cpp

The code is only a representative code showing the inlined version of the loops in question.

Full source code of miniMD can be found at - [The Mantevo Project](https://github.com/Mantevo/mantevo.github.io/tree/master/download_files)

# GROMACS - SPEC CPU 2006

Extended version of the subscripted subscript loops from subroutine 'clincs' along with the code that fills the subscript array.
