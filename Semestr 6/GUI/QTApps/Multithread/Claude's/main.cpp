#include <iostream>
// main.cpp
#include <QApplication>
#include <QDateTime>
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QThread>
#include <QMutex>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>
#include <QScrollBar>

// Character item with timestamp for automatic removal
struct CharacterItem {
    QChar character;
    qint64 timestamp;
    
    CharacterItem(QChar c) : character(c), timestamp(QDateTime::currentMSecsSinceEpoch()) {}
};

// Shared buffer that will be accessed by multiple threads
class SharedBuffer : public QObject
{
    Q_OBJECT

public:
    SharedBuffer(int maxSize = 1000) 
        : m_maxSize(maxSize), m_charLifetime(3000) // Default 3 seconds lifetime
    {
        // Timer for regular cleanup of expired characters
        m_cleanupTimer = new QTimer(this);
        connect(m_cleanupTimer, &QTimer::timeout, this, &SharedBuffer::removeExpiredChars);
        m_cleanupTimer->start(100); // Check every 100ms
    }

    void addChar(QChar c) {
        QMutexLocker locker(&m_mutex);
        m_charItems.append(CharacterItem(c));
        
        // Keep buffer size under control
        if (m_charItems.size() > m_maxSize) {
            m_charItems.removeFirst();
        }
        
        updateBuffer();
    }

    QString getBuffer() const {
        QMutexLocker locker(&m_mutex);
        QString result;
        for (const auto &item : m_charItems) {
            result.append(item.character);
        }
        return result;
    }

    void clear() {
        QMutexLocker locker(&m_mutex);
        m_charItems.clear();
        updateBuffer();
    }
    
    void setCharLifetime(int ms) {
        QMutexLocker locker(&m_mutex);
        m_charLifetime = ms;
    }
    
    int charLifetime() const {
        QMutexLocker locker(&m_mutex);
        return m_charLifetime;
    }

signals:
    void bufferChanged(const QString &buffer);
    void characterExpired(QChar c);

private slots:
    void removeExpiredChars() {
        QMutexLocker locker(&m_mutex);
        
        bool changed = false;
        qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
        
        // Remove characters that have been in the buffer too long
        while (!m_charItems.isEmpty()) {
            const CharacterItem &item = m_charItems.first();
            if (currentTime - item.timestamp > m_charLifetime) {
                QChar expiredChar = item.character;
                m_charItems.removeFirst();
                changed = true;
                emit characterExpired(expiredChar);
            } else {
                // Items are added in chronological order, so if the first isn't expired,
                // no others will be either
                break;
            }
        }
        
        if (changed) {
            updateBuffer();
        }
    }

private:
    void updateBuffer() {
        QString bufferStr;
        for (const auto &item : m_charItems) {
            bufferStr.append(item.character);
        }
        emit bufferChanged(bufferStr);
    }

    QList<CharacterItem> m_charItems;
    mutable QMutex m_mutex;
    int m_maxSize;
    int m_charLifetime; // Time in ms before character is removed
    QTimer *m_cleanupTimer;
};

// Worker thread that generates characters
class CharacterGenerator : public QObject
{
    Q_OBJECT

public:
    CharacterGenerator(SharedBuffer *buffer, int id)
        : m_buffer(buffer), m_id(id), m_active(false), m_interval(500)
    {
        // Set character range based on worker ID
        switch (m_id % 4) {
            case 0: // Lowercase letters
                m_minChar = 'a';
                m_maxChar = 'z';
                break;
            case 1: // Uppercase letters
                m_minChar = 'A';
                m_maxChar = 'Z';
                break;
            case 2: // Numbers
                m_minChar = '0';
                m_maxChar = '9';
                break;
            case 3: // Special characters
                m_minChar = '!';
                m_maxChar = '/';
                break;
        }

        m_timer = new QTimer(this);
        connect(m_timer, &QTimer::timeout, this, &CharacterGenerator::generateCharacter);
    }

    ~CharacterGenerator() {
        stop();
    }

public slots:
    void start() {
        if (!m_active) {
            m_active = true;
            m_timer->start(m_interval);
        }
    }

    void stop() {
        if (m_active) {
            m_active = false;
            m_timer->stop();
        }
    }

    void setInterval(int ms) {
        m_interval = ms;
        if (m_active) {
            m_timer->setInterval(ms);
        }
    }

private slots:
    void generateCharacter() {
        if (m_active) {
            // Generate a random character in our range
            QChar c = QChar(QRandomGenerator::global()->bounded(m_minChar, m_maxChar + 1));
            
            // Add to shared buffer
            m_buffer->addChar(c);
            
            emit characterGenerated(m_id, c);
        }
    }

signals:
    void characterGenerated(int workerId, QChar c);

private:
    SharedBuffer *m_buffer;
    int m_id;
    bool m_active;
    int m_interval;
    QTimer *m_timer;
    ushort m_minChar;
    ushort m_maxChar;
};

// Main window
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent), m_workerCount(0)
    {
        setWindowTitle("Threaded Character Buffer");
        resize(800, 500);
        
        // Create shared buffer
        m_buffer = new SharedBuffer(10000);
        // Connect to the characterExpired signal
        connect(m_buffer, &SharedBuffer::characterExpired, this, &MainWindow::onCharacterExpired);
        connect(m_buffer, &SharedBuffer::bufferChanged, this, &MainWindow::updateBufferDisplay);
        
        // Set up UI
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        
        // Controls
        QHBoxLayout *controlsLayout = new QHBoxLayout();
        
        // Add worker button
        QPushButton *addWorkerBtn = new QPushButton("Add Thread", this);
        connect(addWorkerBtn, &QPushButton::clicked, this, &MainWindow::addWorker);
        controlsLayout->addWidget(addWorkerBtn);
        
        // Remove worker button
        QPushButton *removeWorkerBtn = new QPushButton("Remove Thread", this);
        connect(removeWorkerBtn, &QPushButton::clicked, this, &MainWindow::removeWorker);
        controlsLayout->addWidget(removeWorkerBtn);
        
        // Generation interval control
        QLabel *intervalLabel = new QLabel("Generation (ms):", this);
        controlsLayout->addWidget(intervalLabel);
        
        m_intervalSpinBox = new QSpinBox(this);
        m_intervalSpinBox->setRange(50, 2000);
        m_intervalSpinBox->setValue(500);
        m_intervalSpinBox->setSingleStep(50);
        connect(m_intervalSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateInterval);
        controlsLayout->addWidget(m_intervalSpinBox);
        
        // Character lifetime control
        QLabel *lifetimeLabel = new QLabel("Lifetime (ms):", this);
        controlsLayout->addWidget(lifetimeLabel);
        
        m_lifetimeSpinBox = new QSpinBox(this);
        m_lifetimeSpinBox->setRange(500, 10000);
        m_lifetimeSpinBox->setValue(3000);
        m_lifetimeSpinBox->setSingleStep(500);
        connect(m_lifetimeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateLifetime);
        controlsLayout->addWidget(m_lifetimeSpinBox);
        
        // Clear buffer button
        QPushButton *clearBtn = new QPushButton("Clear Buffer", this);
        connect(clearBtn, &QPushButton::clicked, m_buffer, &SharedBuffer::clear);
        controlsLayout->addWidget(clearBtn);
        
        mainLayout->addLayout(controlsLayout);
        
        // Status section
        QHBoxLayout *statusLayout = new QHBoxLayout();
        
        QLabel *workerCountLabel = new QLabel("Active Threads:", this);
        statusLayout->addWidget(workerCountLabel);
        
        m_workerCountDisplay = new QLabel("0", this);
        statusLayout->addWidget(m_workerCountDisplay);
        
        QLabel *bufferSizeLabel = new QLabel("Buffer Size:", this);
        statusLayout->addWidget(bufferSizeLabel);
        
        m_bufferSizeDisplay = new QLabel("0", this);
        statusLayout->addWidget(m_bufferSizeDisplay);
        
        statusLayout->addStretch();
        
        mainLayout->addLayout(statusLayout);
        
        // Buffer display
        QLabel *bufferLabel = new QLabel("Buffer (chars expire after lifetime):", this);
        mainLayout->addWidget(bufferLabel);
        
        m_bufferDisplay = new QTextEdit(this);
        m_bufferDisplay->setReadOnly(true);
        m_bufferDisplay->setFont(QFont("Courier", 10));
        mainLayout->addWidget(m_bufferDisplay);
        
        // Activity log
        QLabel *logLabel = new QLabel("Activity Log:", this);
        mainLayout->addWidget(logLabel);
        
        m_activityLog = new QTextEdit(this);
        m_activityLog->setReadOnly(true);
        m_activityLog->setMaximumHeight(100);
        mainLayout->addWidget(m_activityLog);
        
        // Start with 2 workers
        addWorker();
        addWorker();
    }

    ~MainWindow() {
        // Clean up all workers
        qDeleteAll(m_workers);
        qDeleteAll(m_workerThreads);
        
        delete m_buffer;
    }

private slots:
    void addWorker() {
        // Create a new thread
        QThread *thread = new QThread();
        m_workerThreads.append(thread);
        
        // Create a worker and move it to the thread
        CharacterGenerator *worker = new CharacterGenerator(m_buffer, m_workerCount);
        worker->moveToThread(thread);
        m_workers.append(worker);
        
        // Connect signals and slots
        connect(thread, &QThread::started, worker, &CharacterGenerator::start);
        connect(thread, &QThread::finished, worker, &CharacterGenerator::deleteLater);
        connect(worker, &CharacterGenerator::characterGenerated, this, &MainWindow::logCharacterGenerated);
        
        // Set interval and start thread
        worker->setInterval(m_intervalSpinBox->value());
        thread->start();
        
        // Update counter
        m_workerCount++;
        m_workerCountDisplay->setText(QString::number(m_workers.size()));
        
        logMessage(QString("Added worker #%1").arg(m_workerCount));
    }
    
    void removeWorker() {
        if (!m_workers.isEmpty()) {
            // Get the last worker and thread
            CharacterGenerator *worker = m_workers.takeLast();
            QThread *thread = m_workerThreads.takeLast();
            
            // Stop worker and thread
            worker->stop();
            thread->quit();
            thread->wait();
            
            // Delete thread and worker
            delete thread;
            delete worker;
            
            // Update counter
            m_workerCountDisplay->setText(QString::number(m_workers.size()));
            
            logMessage("Removed worker");
        }
    }
    
    void updateInterval(int ms) {
        for (auto worker : m_workers) {
            worker->setInterval(ms);
        }
        logMessage(QString("Updated generation interval to %1 ms").arg(ms));
    }
    
    void updateLifetime(int ms) {
        m_buffer->setCharLifetime(ms);
        logMessage(QString("Updated character lifetime to %1 ms").arg(ms));
    }
    
    void updateBufferDisplay(const QString &buffer) {
        m_bufferDisplay->setText(buffer);
        m_bufferSizeDisplay->setText(QString::number(buffer.size()));
        
        // Auto-scroll to bottom
        QScrollBar *scrollBar = m_bufferDisplay->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());
    }
    
    void onCharacterExpired(QChar c) {
        logMessage(QString("Character '%1' expired and was removed from buffer").arg(c));
    }
    
    void logCharacterGenerated(int workerId, QChar c) {
        // Keep log brief - remove old entries when there are too many
        if (m_activityLog->document()->lineCount() > 100) {
            QTextCursor cursor = m_activityLog->textCursor();
            cursor.movePosition(QTextCursor::Start);
            cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor, 50);
            cursor.removeSelectedText();
        }
        
        m_activityLog->append(QString("Thread #%1 generated: '%2'").arg(workerId).arg(c));
    }
    
    void logMessage(const QString &message) {
        m_activityLog->append(message);
    }

private:
    SharedBuffer *m_buffer;
    QList<CharacterGenerator*> m_workers;
    QList<QThread*> m_workerThreads;
    int m_workerCount;
    
    QTextEdit *m_bufferDisplay;
    QTextEdit *m_activityLog;
    QLabel *m_workerCountDisplay;
    QLabel *m_bufferSizeDisplay;
    QSpinBox *m_intervalSpinBox;
    QSpinBox *m_lifetimeSpinBox;
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
