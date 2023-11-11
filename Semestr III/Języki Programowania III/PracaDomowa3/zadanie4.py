import matplotlib.pyplot as plot
import numpy
import math

functionNames = ["print()","len()","input()","range()","type()","str()"]


AxisX = numpy.array([i for i in range(80)])
SinY = numpy.array([math.sin( (math.pi/8) * i ) for i in range(16)])
TanY = numpy.array([math.tan( (math.pi/180) * i ) for i in range(720)])


plot.plot(SinY)
plot.title("Sin(x)")
plot.show()
plot.plot(TanY)
limittan = plot.gca()
limittan.set_ylim([-10,10])
plot.plot()
plot.title("Tan(x)")
plot.show()

