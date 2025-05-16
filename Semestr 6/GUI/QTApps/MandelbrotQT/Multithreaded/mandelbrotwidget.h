#ifndef MANDELBROTWIDGET_H
#define MANDELBROTWIDGET_H

#include <QPoint>
#include <QWidget>

#include "renderthread.h"

class MandelbrotWidget : public QWidget {
    Q_OBJECT

public:
    MandelbrotWidget(QWidget *parent = nullptr);
    ~MandelbrotWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateImage(int rowStart, int rowEnd);

private:
    void initThreads();
    void closeThreads();
    void startRendering();
    void zoom(double factor);

    QImage image;
    QPoint lastDragPos;
    double centerX;
    double centerY;
    double scaleFactor;
    
    // Thread management
    QVector<RenderThread*> threads;
    QMutex mutex;
    int pendingRegions;
    
    // Number of threads to use (typically based on CPU cores)
    static const int THREAD_COUNT = 8; // Adjust based on your system
};

#endif // MANDELBROTWIDGET_H
