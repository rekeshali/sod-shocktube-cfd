###############################################################################
########################### SOD SHOCK TUBE WRAPPER ############################
################################################################################ Rekesh M Ali
# Sod Shocktube program wrapper
import os
import sys
import time
prodir = 'bin/'     # C++ Program location
outdir = 'results/' # output directory
sys.path.append('bin') 
sys.path.append(outdir)
from postsod import Sod, juxtaplot
###############################################################################
################################### INPUTS ####################################
###############################################################################
# Inputs must be in lists
methods  = ['roe'] # steger-warming, roe, or hll
dxs      = [0.0025,0.005,0.01, 0.02, 0.03]
cfls     = [0.4]
###############################################################################
############################### RUN SIMULATION ################################
###############################################################################
# For every combination of inputs above,
# Run C++ Program and log to stdout
# Also saves individual gifs or plots
outfiles = []
for method in methods:
    for dx in dxs:
        for cfl in cfls:
            outfile = method + '-dx' + str(dx) + '-cfl' + str(cfl) + '.sod'
            outfiles.append(outdir + outfile)
            # Note command compiles program before running
            command = ': $(make) && ./bin/sod ' + method + ' ' + str(dx) \
                    + ' ' + str(cfl) + ' ' + outdir + outfile
            print('-'*50)
            print('----Sod CFD with ' + method + ', dx=' + str(dx) + \
                    ', and cfl=' + str(cfl))
            start = time.time()
            os.system(command) # Run C++ exe
            end   = time.time()
            sod = Sod(outdir + outfile) # Read the output file
            print('----Shock tube simulated in %.6f s' % sod.cputime)
            print('----C++Program completed in %.6f s' % (end - start))
            # Plot results
#           sod.plot() # View plot of final tstep
#           sod.gif () # View gif of soltuion
            # Save plot of final tstep
#           sod.plot(save=outdir + 'plots/' + outfile[:-4]+'.png')
            # Gif results and view or save
#           sod.gif (save=outdir + 'gifs/'  + outfile[:-4]+'.gif')
###############################################################################
############################## PLOT COMPARISONS ###############################
###############################################################################
juxtnames = [outdir + outfile, outdir + outfile]
juxtaplot(outfiles, dxs)
###############################################################################
################################### END #######################################
###############################################################################
