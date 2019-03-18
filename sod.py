# Sod Shocktube program wrapper
# Run and save or view plots/gifs
import os
import sys
sys.path.append('bin')
from plotsod import Sod
#################################################################
############################ INPUTS #############################
#################################################################
method  = 'hll' # steger-warming, roe, or hll
dx  = 0.005
cfl = 0.5
outfile = method + '-dx' + str(dx) + '-cfl' + str(cfl) + '.sod'
#################################################################
#################################################################
#################################################################
# Run command
command = './bin/sod ' + method + ' ' + str(dx) + ' ' + str(cfl) + ' ' + outfile
os.system(command)
# Plot results
sod = Sod(outfile)
sod.gif()
