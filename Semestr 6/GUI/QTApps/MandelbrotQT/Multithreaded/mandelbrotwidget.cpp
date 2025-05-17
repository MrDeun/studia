#include "mandelbrotwidget.h"
#include "renderthread.h"
#include <QPainter>
#include <QMouseEvent>

MandelbrotWidget::MandelbrotWidget(QWidget *parent)
    : QWidget(parent), centerX(0.0), centerY(0.0), scaleFactor(4.0),
      pendingRegions(0) {

  setMouseTracking(true);
  setFocusPolicy(Qt::StrongFocus);

  image = QImage(size(), QImage::Format_RGB32);
  image.fill(Qt::white);

  initThreads();

  startRendering();
}
MandelbrotWidget::~MandelbrotWidget() { closeThreads(); }

void MandelbrotWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}
void MandelbrotWidget::resizeEvent(QResizeEvent *event) { // Create a new image with the new size
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
void MandelbrotWidget::wheelEvent(QWheelEvent *event) {
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
void MandelbrotWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastDragPos = event->pos();
    }
}
void MandelbrotWidget::mouseMoveEvent(QMouseEvent *event) {
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
void MandelbrotWidget::keyPressEvent(QKeyEvent *event) {
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
void MandelbrotWidget::updateImage(int rowStart, int rowEnd) {
        update(0, rowStart, width(), rowEnd - rowStart + 1);
        {
            QMutexLocker locker(&mutex);
            pendingRegions--;
            if (pendingRegions == 0) {
                update();
            }
        }
}
void MandelbrotWidget::initThreads() {
  for (int i = 0; i < THREAD_COUNT; i++) {
    RenderThread *thread = new RenderThread(this);
    connect(thread, &RenderThread::renderedImage, this,
            &MandelbrotWidget::updateImage);
    threads.append(thread);
  }
}
void MandelbrotWidget::closeThreads() {
  for (int i = 0; i < threads.size(); i++) {
    threads[i]->abort();
    threads[i]->wait();
  }
  qDeleteAll(threads);
  threads.clear();
}
void MandelbrotWidget::startRendering() {
  for (int i = 0; i < threads.size(); i++) {
    threads[i]->abort();
  }
  int height = image.height();
  int rowsPerThread = height / threads.size();
  {
    QMutexLocker locker(&mutex);
    pendingRegions = threads.size();
  }
  for (int i = 0; i < threads.size(); i++) {
    int rowStart = i * rowsPerThread;
    int rowEnd =
        (i == threads.size() - 1) ? height - 1 : (i + 1) * rowsPerThread - 1;
    threads[i]->render(&image, centerX, centerY, scaleFactor, rowStart, rowEnd);
  }
}
void MandelbrotWidget::zoom(double factor) {
    scaleFactor *= factor;
    startRendering();
    update();
}