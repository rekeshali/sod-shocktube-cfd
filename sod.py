# Sod Shocktube program wrapper
# Run and save or view plots/gifs
import os
import sys
import time
sys.path.append('bin')
from plotsod import Sod
outdir = 'results/'
sys.path.append(outdir)
#################################################################
############################ INPUTS #############################
#################################################################
method  = 'hll' # steger-warming, roe, or hll
dx  = 0.005
cfl = 0.5
outfile = outdir + method + '-dx' + str(dx) + '-cfl' + str(cfl) + '.sod'
#################################################################
#################################################################
#################################################################
# Run command
command = './bin/sod ' + method + ' ' + str(dx) + ' ' + str(cfl) + ' ' + outfile
start = time.time()
# os.system(command) # Run C++ exe, must compile with make first
print('Sod CFD with ' + method + ', dx=' + str(dx) + ', and cfl=' + str(cfl) + ' in ' + str(time.time() - start) + ' s')
# Plot results
sod = Sod(outfile) # Read the output file
# sod.plot() # View plot of final tstep
sod.gif () # View gif of soltuion
# sod.plot(save=outfile[:-4]+'.png') # Save plot of final tstep
# sod.gif (save=outfile[:-4]+'.gif') # Gif results and view or save
