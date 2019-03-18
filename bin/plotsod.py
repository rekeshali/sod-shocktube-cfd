import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

class Sod:
    fname = None
    td    = None
    x     = None
    data  = None
    fig = None
    ax1 = None
    ax2 = None
    ax3 = None
    axes   = None
    alims  = None
    ylabel = ['Density','Velocity','Pressure']

    def __init__(self, fname):
        self.fname = fname
        self.read(fname)
        return

    def read(self, fname):
        data = []
        f = open(fname,'r')
        for line in f:
            point = list(map(float, line.split()))
            if len(point) > 2:
                data.append(list(map(float, line.split())))
            else:
                td, jd = list(map(int, point))
        self.data = np.array(data).reshape((td,jd,3))
        self.x = np.arange(0, 1, 1/jd)
        self.alims = []
        for i in range(3):
            self.alims.append(np.max(self.data[-1,:,i]))
        self.td = td
        return

    def plot_init(self):
        self.fig, (self.ax1, self.ax2, self.ax3) = plt.subplots(1,3, figsize=(12,4))
        self.axes = [self.ax1, self.ax2, self.ax3]
        self.fig.tight_layout()
        self.fig.subplots_adjust(left=0.05, bottom=0.12)
        for i, ax in enumerate(self.axes):
            self.plot_same(ax, i)

    def plot_same(self,ax, i):
            ax.set_xlabel("X");
            ax.set_ylabel(self.ylabel[i])
            ax.set_xlim([0,1])
            ax.set_ylim([0,1.05*self.alims[i]])

    def plot_time(self, t):
        for i, ax in enumerate(self.axes):
            ax.clear();
            ax.plot(self.x, self.data[t,:,i])
            self.plot_same(ax, i)

    def plot(self, t=-1, save=None):
        self.plot_init()
        self.plot_time(t)
        if save is not None:
            plt.savefig(save)
        else:
            plt.show()

    def gif_init(self):
        self.plot_time(0)

    def gif_update(self, i):
        self.plot_time(i);

    def gif(self, fps=60, save=None):
        ms = 1000/fps
        self.plot_init();
        ani = animation.FuncAnimation( self.fig, self.gif_update,
                init_func=self.gif_init, frames=self.td, interval=ms)
        if save is not None:
            ani.save(save, writer='imagemagick', fps=20)
        else:
            plt.show()
