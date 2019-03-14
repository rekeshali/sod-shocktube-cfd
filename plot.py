import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

class Sod:
    fname = "out"
    td = None
    jd = None
    data = None
    x = None
    fig = None
    ax = None
    qplt = None
    def __init__(self, fname):
        self.fname = fname
        self.read(fname)
        return

    def read(self, fname):
        data = []
        f = open(fname,'r')
        td, jd = list(map(int, f.readline().split()))
        self.x = np.arange(0, 1, 1/jd)
        for line in f:
            data.append(list(map(float, line.split())))
        self.data = np.array(data).reshape((td,jd,3))
        self.td, self.jd = [td, jd]
        return

    def init(self):
        self.ax.plot(self.x, self.data[0,:,self.qplt])

    def animate(self, i):
        self.ax.clear()
        self.ax.plot(self.x, self.data[i,:,self.qplt])  # update the data.

    def plot(self, q=0, fps=20):
        ms = 1000/fps
        self.qplt = q
        self.fig, self.ax = plt.subplots()
        ani = animation.FuncAnimation( self.fig, self.animate, init_func=self.init,
                frames=self.td, interval=ms)
        plt.show()

q = Sod('out')
q.plot()
