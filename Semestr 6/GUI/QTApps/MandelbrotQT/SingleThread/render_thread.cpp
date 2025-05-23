#include "render_thread.h"
#include <qforeach.h>
#include <qmutex.h>
#include <qthread.h>

RenderThread::RenderThread(QObject *parent) : QThread(parent) {
  for (int i = 0; i < Colormapsize; ++i) {
    colormap[i] = rgbFromWaveLength(380.0 + (i * 400.0 / Colormapsize));
  }
}
RenderThread::~RenderThread() {
  mutex.lock();
  abort = true;
  condition.wakeOne();
  mutex.unlock();

  wait();
}

void RenderThread::render(double x, double y, double scale, QSize resultSize,
                          double pixelRatio) {
  QMutexLocker locker(&mutex);

  this->centerX = x;
  this->centerY = y;
  this->scaleFactor = scale;
  this->devicePixelRatio = pixelRatio;
  this->resultSize = resultSize;

  if (!isRunning()) {
    start(LowPriority);
  } else {
    restart = true;
    condition.wakeOne();
  }
}

void RenderThread::run() {
  forever {
    mutex.lock();
    const double devicePixelRatio = this->devicePixelRatio;
    const QSize resultSize = this->resultSize * devicePixelRatio;
    const double requestedScaleFactor = this->scaleFactor;
    const double scaleFactor = requestedScaleFactor / devicePixelRatio;

    const double centerX = this->centerX;
    const double centerY = this->centerY;
    mutex.unlock();

    int halfWidth = resultSize.width() / 2;
    int halfHeight = resultSize.height() / 2;

    QImage image(resultSize, QImage::Format_RGB32);
    image.setDevicePixelRatio(devicePixelRatio);

    const int NumPasses = 16;
    int pass = 0;
    while (pass < NumPasses) {
      const int MaxIterations = (1 << (2 * pass + 6)) + 32;
      const int Limit = 8;

      bool allBlack = true;

      for (int y = -halfHeight; y < halfHeight; ++y) {
        if (restart)
          break;
        if (abort)
          return;

        auto scanLine =
            reinterpret_cast<uint *>(image.scanLine(y + halfHeight));
        const double ay = centerY + (y * scaleFactor);

        for (int x = -halfWidth; x < halfWidth; ++x) {
          const double ax = centerX + (x * scaleFactor);
          double a1 = ax;
          double b1 = ay;
          int numIterations = 0;

          do {
            auto a2 = a1*a1 - b1*b1;
            auto b2 = 2.0 * a1 * b1;
            
            a1 = a2 + ax;
            b1 = b2 + ay;

            if(abs(a1 + b1) > Limit)
                break;

            numIterations++;
          } while (numIterations < MaxIterations);

          if(numIterations < MaxIterations){
            *scanLine++ = colormap[numIterations % Colormapsize];
            allBlack = false;
          } else {
            *scanLine++ = qRgb(0,0,0);
          }
        }
      }
      if(allBlack && pass == 0){
        pass = 4;
      } else {
        if(!restart) 
            emit renderedImage(image, requestedScaleFactor);
        ++pass;
      }
    }
    mutex.lock();
    if(!restart)
        condition.wait(&mutex);
    restart = false;
    mutex.unlock();
  }
}

uint RenderThread::rgbFromWaveLength(double wave) {
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    if (wave >= 380.0 && wave <= 440.0) {
        r = -1.0 * (wave - 440.0) / (440.0 - 380.0);
        b = 1.0;
    } else if (wave >= 440.0 && wave <= 490.0) {
        g = (wave - 440.0) / (490.0 - 440.0);
        b = 1.0;
    } else if (wave >= 490.0 && wave <= 510.0) {
        g = 1.0;
        b = -1.0 * (wave - 510.0) / (510.0 - 490.0);
    } else if (wave >= 510.0 && wave <= 580.0) {
        r = (wave - 510.0) / (580.0 - 510.0);
        g = 1.0;
    } else if (wave >= 580.0 && wave <= 645.0) {
        r = 1.0;
        g = -1.0 * (wave - 645.0) / (645.0 - 580.0);
    } else if (wave >= 645.0 && wave <= 780.0) {
        r = 1.0;
    }

    double s = 1.0;
    if (wave > 700.0)
        s = 0.3 + 0.7 * (780.0 - wave) / (780.0 - 700.0);
    else if (wave <  420.0)
        s = 0.3 + 0.7 * (wave - 380.0) / (420.0 - 380.0);

    r = std::pow(r * s, 0.8);
    g = std::pow(g * s, 0.8);
    b = std::pow(b * s, 0.8);
    return qRgb(int(r * 255), int(g * 255), int(b * 255));
}