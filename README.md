# sod-shocktube-cfd
Sod shocktube using Explicit Euler in time and Steger-Warming, Roe, or HLL in space.

Computation in C++, visualization python.

### To Compile: 

make

### To Run:

./bin/sod method dx cfl outfile

-or-

py sod.py  ## change inputs in sod.py

### To Plot:

Use Sod class in plotsod.py to read and plot from outfile.

sod = Sod(outfile)

sod.plot()  ## plots final tstep

sod.gif()  ## animates run

sod.plot(save=fname)  ## saves plot or gif to fname
