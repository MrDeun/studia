#include "renderthread.h"
#include <QImage>
#include <complex>
#include <qforeach.h>
#include <qmutex.h>
#include <qobject.h>
#include <qrgb.h>
#include <qthread.h>
#include <qtmetamacros.h>



MandelbrotThread::MandelbrotThread(QObject *parent)
    : QThread(parent), _abort(false)
{
}

MandelbrotThread::~MandelbrotThread()
{
    mutex.lock();
    _abort = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void MandelbrotThread::render(double cX, double cY, double scale, 
                             int imgWidth, int imgHeight, int start, int end)
{
    QMutexLocker locker(&mutex);
    
    this->imageWidth = imgWidth;
    this->imageHeight = imgHeight;
    this->centerX = cX;
    this->centerY = cY;
    this->scaleFactor = scale;
    this->rowStart = start;
    this->rowEnd = end;
    
    if (!isRunning()) {
        run();
    } else {
        restart = true;
        condition.wakeOne();
    }
}

void MandelbrotThread::abort()
{
    QMutexLocker locker(&mutex);
    _abort = true;
    condition.wakeOne();
}

void MandelbrotThread::run()
{
    forever {
        // Get the rendering parameters
        mutex.lock();
        int localWidth = imageWidth;
        int localHeight = imageHeight;
        double localCenterX = centerX;
        double localCenterY = centerY;
        double localScaleFactor = scaleFactor;
        int localRowStart = rowStart;
        int localRowEnd = rowEnd;
        mutex.unlock();
        
        // Create a fragment image for this thread's portion
        QImage fragmentImage(localWidth, localRowEnd - localRowStart + 1, QImage::Format_RGB32);
        double aspectRatio = static_cast<double>(localWidth) / localHeight;
        
        for (int y = 0; y < fragmentImage.height(); ++y) {
            if (_abort)
                break;
                
            // Calculate the actual y-coordinate in the complete image
            int actualY = y + localRowStart;
                
            // Calculate the row of pixels
            QRgb *row = reinterpret_cast<QRgb*>(fragmentImage.scanLine(y));
            
            for (int x = 0; x < localWidth; ++x) {
                // Map pixel coordinates to the complex plane
                double real = localCenterX + (x - localWidth/2.0) * localScaleFactor / localWidth * aspectRatio;
                double imag = localCenterY + (actualY - localHeight/2.0) * localScaleFactor / localHeight;
                std::complex<double> c(real, imag);
                
                // Compute the number of iterations
                int iterations = computeIterations(c);
                
                // Convert iterations to color
                if (iterations == MAX_ITERATIONS) {
                    row[x] = qRgb(0, 0, 0); // Black for points in the set
                } else {
                    // Map iterations to a color - using a simple gradient for this example
                    int r = static_cast<int>(255.0 * iterations / MAX_ITERATIONS);
                    int g = static_cast<int>(140.0 * iterations / MAX_ITERATIONS);
                    int b = static_cast<int>(255.0 * iterations / MAX_ITERATIONS);
                    row[x] = qRgb(r, g, b);
                }
            }
        }
        
        // Notify that this fragment is complete with the image data and position
        if (!_abort)
            emit renderedImageFragment(fragmentImage.copy(), 0, localRowStart);
        
        // Wait for the next job or exit if aborted
        mutex.lock();
        if (!restart && !_abort)
            condition.wait(&mutex);
        restart = false;
        
        // Check if we need to exit the thread
        if (_abort) {
            mutex.unlock();
            return;
        }
        mutex.unlock();
    }
}

int MandelbrotThread::computeIterations(const std::complex<double> &c)
{
    std::complex<double> z = 0;
    int iterations = 0;
    
    while (std::abs(z) < 2.0 && iterations < MAX_ITERATIONS) {
        z = z * z + c;
        iterations++;
    }
    
    return iterations;
}