#include "renderthread.h"
#include <QImage>
#include <complex>
#include <qforeach.h>
#include <qmutex.h>
#include <qobject.h>
#include <qrgb.h>
#include <qtmetamacros.h>



RenderThread::RenderThread(QObject *parent) : QThread(parent), _abort(false) {}

void RenderThread::render(QImage *image, double centerX, double centerY,
                          double scaleFactor, int rowStart, int rowEnd) {
  QMutexLocker locker(&RenderThread::mutex);

  this->image = image;
  this->centerX = centerX;
  this->centerY = centerY;
  this->scaleFactor = scaleFactor;
  this->rowStart = rowStart;
  this->rowEnd = rowEnd;

  if (!isRunning()) {
    start();
  } else {
    restart = true;
    condition.wakeOne();
  }
}
void RenderThread::abort() {
    QMutexLocker locker(&RenderThread::mutex);
    _abort = true;
    condition.wakeOne();
}
void RenderThread::run() {
  forever {
    RenderThread::mutex.lock();
    QImage *localImage = image;
    double localCenterX = centerX;
    double localCenterY = centerY;
    double localScaleFactor = scaleFactor;
    int localRowStart = rowStart;
    int localRowEnd = rowEnd;
    RenderThread::mutex.unlock();

    int width = localImage->width();
    int height = localImage->height();
    double aspectRadio = static_cast<double>(width) / height;

    for (int y = localRowStart; y <= localRowEnd; y++) {
      if (_abort)
        break;

      uchar *scanLine = localImage->scanLine(y);
      QRgb *row = reinterpret_cast<QRgb *>(scanLine);

      for (int x = 0; x < width; ++x) {
        double real = localCenterX + (x - width / 2.0) * localScaleFactor;
        double imag = localCenterY + (y - width / 2.0) * localScaleFactor;

        std::complex<double> c(real, imag);

        int iterations = computeIterations(c);

        if (iterations == MAX_ITERATIONS) {
          row[x] = qRgb(0, 0, 0);
        } else {
          int r = static_cast<int>(255.0 * iterations / MAX_ITERATIONS);
          int g = static_cast<int>(140.0 * iterations / MAX_ITERATIONS);
          int b = static_cast<int>(255.0 * iterations / MAX_ITERATIONS);
          row[x] = qRgb(r, g, b);
        }
      }
    }
    if (!_abort)
      emit renderedImage(localRowStart, localRowEnd);

      RenderThread::mutex.lock();
    if (!restart && !_abort)
      condition.wait(&mutex);
    restart = false;

    if (_abort) {
      RenderThread::mutex.unlock();
      return;
    }
    return;
  }
}
int RenderThread::computeIterations(const std::complex<double> &c) {
  std::complex<double> z = 0.0;
  int iterations = 0;
  while (std::abs(z) < MAX_LIMIT && iterations < MAX_ITERATIONS) {
    z = z * z + c;
    iterations++;
  }
  return iterations;
}

RenderThread::~RenderThread() {
  RenderThread::mutex.lock();
  _abort = true;
  condition.wakeOne();
  RenderThread::RenderThread::mutex.unlock();
  wait();
}