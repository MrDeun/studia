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

    void render( double centerX, double centerY, double scaleFactor, QSize imgSize,
                int rowStart, int rowEnd);
    void abort();

signals:
    void renderedImage(QImage image,int rowStart, int rowEnd);

protected:
    void run() override;

private:
    int computeIterations(const std::complex<double> &c);

    QMutex mutex;
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
    static constexpr int MAX_ITERATIONS = 1000;
    static constexpr double MAX_LIMIT = 2.0;
};

#endif