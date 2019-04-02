# sod-shocktube-cfd
Sod shocktube using Explicit Euler in time and Steger-Warming, Roe, or HLL in space. Traditional initial conditions, constant solution boundaries.

Computation in C++, visualization python.

### To Compile: 

make

### To Run & Plot:

py sod.py  # change inputs in sod.py *will run make

### To Run:

./bin/sod method dx cfl outfile


### To Plot:

from plotsod import Sod

sod = Sod(outfile) # read data from outfile

sod.plot()  # plots final tstep

sod.gif()  # animates run

juxtaplot(outfiles, legend) # comparison plot of multiple runs

sod.plot(save=figname)  # saves fig to figname. For plot, gif, or juxtaplot
