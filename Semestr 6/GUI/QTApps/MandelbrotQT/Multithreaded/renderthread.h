#ifndef RENDER_THREAD
#define RENDER_THREAD

#include <complex>

#include <QThread>
#include <QWaitCondition>
#include <QMutex>

class MandelbrotThread : public QThread {
    Q_OBJECT

public:
    MandelbrotThread(QObject *parent = nullptr);
    ~MandelbrotThread();

    // Set the region this thread will compute
    void render(double centerX, double centerY, double scaleFactor, 
                int imgWidth, int imgHeight, int rowStart, int rowEnd);
    void abort();

signals:
    // Signal emitted with the image fragment and its position
    void renderedImageFragment(QImage fragment, int x, int y);

protected:
    void run() override;

private:
    // Compute the number of iterations for a point in the complex plane
    int computeIterations(const std::complex<double> &c);

    QMutex mutex;
    QWaitCondition condition;
    int imageWidth;
    int imageHeight;
    double centerX;
    double centerY;
    double scaleFactor;
    int rowStart;
    int rowEnd;
    bool restart;
    bool _abort;

    // Maximum iterations for the Mandelbrot calculation
    static const int MAX_ITERATIONS = 1000;
};
#endif