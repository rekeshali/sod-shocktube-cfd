# sod-shocktube-cfd
Sod shocktube using Explicit Euler in time and Steger-Warming, Roe, or HLL in space.

Computation in C++, visualization python.

### To Compile: 

make

### To Run & Plot:

py sod.py  # change inputs in sod.py

### To Run:

./bin/sod method dx cfl outfile


### To Plot:

from plotsod import Sod

sod = Sod(outfile) # read data from outfile

sod.plot()  # plots final tstep

sod.gif()  # animates run

sod.plot(save=fname)  # saves plot or gif to fname
