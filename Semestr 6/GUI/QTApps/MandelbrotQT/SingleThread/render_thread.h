#ifndef RENDER_THREAD
#define RENDER_THREAD

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSize>
#include <QImage>
#include <qtmetamacros.h>
class RenderThread : public QThread {
    Q_OBJECT

    public:
        RenderThread(QObject *parent=nullptr);
        ~RenderThread();

        void render(double centerX, double centerY, double scaleFactor, QSize resultSize, double devicePixelRatio);

    signals:
        void renderedImage(const QImage &image, double scaleFactor);
    
    protected:
        void run() override;
    
    private:
        static uint rgbFromWaveLength(double wave);

        QMutex mutex;
        QWaitCondition condition;

        double centerX;
        double centerY;
        double scaleFactor;
        double devicePixelRatio;
        QSize resultSize;
        
        bool restart = false;
        bool abort = false;

        enum {Colormapsize = 512};
        uint colormap[Colormapsize];

};

#endif