import matplotlib.pyplot as plot
import numpy
import math

# matplotlib mozna wyswietlic wykresy danych

functionNames = ["str()","type()","range()","input()","len()","print()"]
functionStats = [math.log( (6-i) * 5 ) for i in range (6)]

AxisX = numpy.array([i for i in range(80)])
SinY = numpy.array([math.sin( (math.pi/8) * i ) for i in range(16)])
TanY = numpy.array([math.tan( (math.pi/180) * i ) for i in range(720)])



def performTask4():
    plot.plot(SinY)
    plot.title("Sin(x)")
    plot.show()
    plot.plot(TanY)
    limittan = plot.gca()
    limittan.set_ylim([-10,10])
    plot.plot()
    plot.title("Tan(x)")
    plot.show()

    plot.bar(functionNames,functionStats)
    plot.show()

