import numpy as np
from cycler import cycler
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.animation as animation
mpl.rcParams['axes.prop_cycle'] = cycler(color='rgbcmyk')
# Sod class can read data and plot rho, velocity, and Pressure
class Sod:
    fname = None # filename
    td    = None # frames
    x     = None # position
    data  = None # q for all frames
    cputime = None # time of simulation
    fig = None # fig handle
    ax1 = None # subplot axes
    ax2 = None
    ax3 = None
    axes   = None # list of subplot axes
    alims  = None # list of axis limits
    ylabel = ['Density','Velocity','Pressure']

    # object initializer
    def __init__(self, fname=None):
        if fname is not None:
            self.fname = fname
            self.read(fname)
        return

    ##########################
    ###### GETTING DATA ######
    ##########################
    # read data from ouput of sod program
    def read(self, fname):
        data = []
        f = open(fname,'r')
        for line in f:
            point = line.split() # split by space
            if len(point) == 3:  # q per point is of length 3
                data.append(list(map(float, point))) # stack onto list
            else: # line without 3 vals has simulation params
                td, jd = list(map(int, point[1:3]))
                self.cputime = float(point[3])
        self.data  = np.array(data).reshape((td,jd,3)) # convert list to array
        self.x     = np.arange(0, 1, 1/jd) # create position vector
        self.td    = td
        self.alims = []
        for i in range(3): # find max vals for axis lims
            self.alims.append(np.max(self.data[-1,:,i]))
        return

    ######################
    ###### PLOTTING ######
    ######################
    # initialize figure with axes and format
    def plot_init(self):
        # open fig and make axes
        self.fig, (self.ax1, self.ax2, self.ax3) = plt.subplots(1,3, \
                figsize=(12,4))
        self.axes = [self.ax1, self.ax2, self.ax3]
        self.fig.tight_layout() # pretty 
        self.fig.subplots_adjust(left=0.05, bottom=0.12) # pretty
        for i, ax in enumerate(self.axes):
            self.plot_same(ax, i)

    # axis formatting
    def plot_same(self,ax, i):
            ax.set_xlabel("X");
            ax.set_ylabel(self.ylabel[i])
            ax.set_xlim([0,1])
            ax.set_ylim([0,1.05*self.alims[i]])

    # plot a frame and format axes
    def plot_time(self, t=-1, clear=True):
        for i, ax in enumerate(self.axes):
            if clear is True:
                ax.clear();
            ax.plot(self.x, self.data[t,:,i],linewidth=1.25)
            self.plot_same(ax, i)

    # plot and show or save
    def plot(self, t=-1, save=None):
        self.plot_init()
        self.plot_time(t)
        if save is not None:
            plt.savefig(save)
        else:
            plt.show()

    #######################
    ###### ANIMATING ######
    #######################
    # initialize first frame in gif
    def gif_init(self):
        self.plot_time(0)

    # gets called by gif for every frame
    def gif_update(self, i):
        self.plot_time(i);

    # make gif and show or save
    def gif(self, fps=60, save=None):
        ms = 1000/fps
        self.plot_init();
        ani = animation.FuncAnimation( self.fig, self.gif_update,
                init_func=self.gif_init, frames=self.td, interval=ms)
        if save is not None:
            ani.save(save, writer='imagemagick', fps=20)
        else:
            plt.show()
##############################################################################
# Sod class can be used to plot multiple runs on the same axes
def juxtaplot(fnames, legend=None, save=None):
    sod = Sod()
    umax = 0
    for n, fname in enumerate(fnames): # for all run files
        sod.read(fname) # read in new data
        if n is 0: # initialize plot on first iteration
            sod.plot_init()
        sod.plot_time(clear=False) # plot new data on top
        if sod.alims[1] > umax: # find largest vel lim
            umax  = sod.alims[1]
    sod.alims[1] = umax
    sod.plot_same(sod.ax2, 1) # make sure lergest vel fits
    if legend is not None:
        plt.legend(legend)
    if save is not None:
        plt.savefig(save)
    else:
        plt.show()
