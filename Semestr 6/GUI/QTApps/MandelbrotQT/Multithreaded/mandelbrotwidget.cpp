#include "mandelbrotwidget.h"
#include "renderthread.h"
#include <QPainter>
#include <QMouseEvent>
#include <qnamespace.h>
#include <qpainter.h>

MandelbrotWidget::MandelbrotWidget(QWidget *parent)
    : QWidget(parent), centerX(0.0), centerY(0.0), scaleFactor(4.0), pendingRegions(0)
{
    // Enable mouse tracking for smooth dragging
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    
    // Create a blank image
    image = QImage(size(), QImage::Format_RGB32);
    image.fill(Qt::white);
    
    // Initialize worker threads
    initThreads();
    
    // Start the initial rendering
    startRendering();
}

MandelbrotWidget::~MandelbrotWidget()
{
    closeThreads();
}

void MandelbrotWidget::initThreads()
{
    // Create and store worker threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        MandelbrotThread *thread = new MandelbrotThread(this);
        connect(thread, &MandelbrotThread::renderedImageFragment, 
                this, &MandelbrotWidget::updateImageFragment,Qt::QueuedConnection);
        threads.append(thread);
    }
}

void MandelbrotWidget::closeThreads()
{
    // Clean up all threads
    for (int i = 0; i < threads.size(); i++) {
        threads[i]->abort();
        threads[i]->wait();
    }
    qDeleteAll(threads);
    threads.clear();
}

void MandelbrotWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void MandelbrotWidget::resizeEvent(QResizeEvent *event)
{
    // Create a new image with the new size
    QImage newImage(event->size(), QImage::Format_RGB32);
    newImage.fill(Qt::white);
    
    // Copy the old image if possible
    if (!image.isNull()) {
        QPainter painter(&newImage);
        painter.drawImage(0, 0, image);
    }
    
    image = newImage;
    startRendering();
}

void MandelbrotWidget::wheelEvent(QWheelEvent *event)
{
    // Get the position where the wheel event occurred
    QPointF pos = event->position();
    
    // Get the distance of the scroll (positive for zooming in, negative for zooming out)
    int numDegrees = event->angleDelta().y() / 8;
    int numSteps = numDegrees / 15;
    
    // Calculate zoom factor (typically 1.2 or so for each step)
    double factor = pow(1.2, numSteps);
    
    // Zoom centered at the mouse position
    double mouseX = centerX + (pos.x() - width()/2.0) * scaleFactor / width();
    double mouseY = centerY + (pos.y() - height()/2.0) * scaleFactor / height();
    
    // New center position after zoom
    centerX = mouseX - (mouseX - centerX) / factor;
    centerY = mouseY - (mouseY - centerY) / factor;
    
    // Apply the zoom factor
    scaleFactor /= factor;
    
    startRendering();
    update();
}

void MandelbrotWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastDragPos = event->pos();
    }
}

void MandelbrotWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        // Calculate the distance moved
        QPoint delta = event->pos() - lastDragPos;
        lastDragPos = event->pos();
        
        // Move the center accordingly, taking scale into account
        centerX -= delta.x() * scaleFactor / width();
        centerY -= delta.y() * scaleFactor / height();
        
        startRendering();
        update();
    }
}

void MandelbrotWidget::keyPressEvent(QKeyEvent *event)
{
    // Allow keyboard navigation
    switch (event->key()) {
    case Qt::Key_Plus:
    case Qt::Key_Equal:
        zoom(0.8); // Zoom in
        break;
    case Qt::Key_Minus:
        zoom(1.25); // Zoom out
        break;
    case Qt::Key_Left:
        centerX -= 0.1 * scaleFactor;
        startRendering();
        break;
    case Qt::Key_Right:
        centerX += 0.1 * scaleFactor;
        startRendering();
        break;
    case Qt::Key_Up:
        centerY -= 0.1 * scaleFactor;
        startRendering();
        break;
    case Qt::Key_Down:
        centerY += 0.1 * scaleFactor;
        startRendering();
        break;
    case Qt::Key_Home:
        // Reset to default view
        centerX = 0.0;
        centerY = 0.0;
        scaleFactor = 4.0;
        startRendering();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
    
    update();
}

void MandelbrotWidget::zoom(double factor)
{
    scaleFactor *= factor;
    startRendering();
    update();
}

void MandelbrotWidget::startRendering()
{
    // Abort any ongoing rendering
    for (int i = 0; i < threads.size(); i++) {
        threads[i]->abort();
    }
    
    // Set up the regions for each thread
    int height = image.height();
    int rowsPerThread = height / threads.size();
    
    {
        QMutexLocker locker(&mutex);
        pendingRegions = threads.size();
    }
    
    // Start rendering each region
    for (int i = 0; i < threads.size(); i++) {
        
        int rowStart = i * rowsPerThread;
        int rowEnd = (i == threads.size() - 1) ? height - 1 : (i + 1) * rowsPerThread - 1;
        threads[i]->sleep(10*i);
        threads[i]->render(centerX, centerY, scaleFactor, 
                           image.width(), image.height(), rowStart, rowEnd);
    }
}

void MandelbrotWidget::updateImageFragment(QImage fragment, int x, int y)
{
    // Use QPainter to draw the fragment onto the main image at the specified position
    QPainter painter(&image);
    painter.drawImage(x, y, fragment);
    
    // Update the widget to show the newly rendered region
    update(x, y, fragment.width(), fragment.height());
    
    // Check if all regions are complete
    {
        QMutexLocker locker(&mutex);
        pendingRegions--;
        if (pendingRegions == 0) {
            // All regions are complete, update the entire widget
            update();
        }
    }
}
