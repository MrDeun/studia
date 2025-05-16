#ifndef RENDER_THREAD
#define RENDER_THREAD

#include <complex>

#include <QThread>
#include <QWaitCondition>
#include <QMutex>

class RenderThread : public QThread {
    Q_OBJECT

public:
    RenderThread(QObject *parent = nullptr);
    ~RenderThread();

    void render(QImage *image, double centerX, double centerY, double scaleFactor, 
                int rowStart, int rowEnd);
    void abort();

signals:
    void renderedImage(int rowStart, int rowEnd);

protected:
    void run() override;

private:
    int computeIterations(const std::complex<double> &c);

    static QMutex mutex;
    QWaitCondition condition;
    QImage *image;
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