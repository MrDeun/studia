#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFont>

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent)
{
    setWindowTitle("Simple Character Thread App");
    resize(600, 400);
    
    // Create the shared buffer
    m_buffer = new SharedBuffer(this);
    connect(m_buffer, &SharedBuffer::bufferUpdated, 
            this, &MainWindow::updateBufferDisplay);
    connect(m_buffer, &SharedBuffer::characterAdded,
            this, &MainWindow::logCharacterAdded);
    connect(m_buffer, &SharedBuffer::characterPopped,
            this, &MainWindow::logCharacterPopped);
    
    // Create central widget and layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // Control buttons layout
    QHBoxLayout *controlLayout = new QHBoxLayout();
    
    // Add thread button
    QPushButton *addThreadBtn = new QPushButton("Add Thread", this);
    connect(addThreadBtn, &QPushButton::clicked, this, &MainWindow::addThread);
    controlLayout->addWidget(addThreadBtn);
    
    // Remove thread button
    QPushButton *removeThreadBtn = new QPushButton("Remove Thread", this);
    connect(removeThreadBtn, &QPushButton::clicked, this, &MainWindow::removeThread);
    controlLayout->addWidget(removeThreadBtn);
    
    // Generate interval control
    QLabel *genIntervalLabel = new QLabel("Generate (ms):", this);
    controlLayout->addWidget(genIntervalLabel);
    
    m_generateIntervalSpinBox = new QSpinBox(this);
    m_generateIntervalSpinBox->setRange(100, 3000);
    m_generateIntervalSpinBox->setValue(1000);
    m_generateIntervalSpinBox->setSingleStep(100);
    connect(m_generateIntervalSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::updateGenerateInterval);
    controlLayout->addWidget(m_generateIntervalSpinBox);
    
    // Pop interval control
    QLabel *popIntervalLabel = new QLabel("Pop (ms):", this);
    controlLayout->addWidget(popIntervalLabel);
    
    m_popIntervalSpinBox = new QSpinBox(this);
    m_popIntervalSpinBox->setRange(100, 3000);
    m_popIntervalSpinBox->setValue(1000);
    m_popIntervalSpinBox->setSingleStep(100);
    connect(m_popIntervalSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::updatePopInterval);
    controlLayout->addWidget(m_popIntervalSpinBox);
    
    // Clear button
    QPushButton *clearBtn = new QPushButton("Clear", this);
    connect(clearBtn, &QPushButton::clicked, m_buffer, &SharedBuffer::clear);
    controlLayout->addWidget(clearBtn);
    
    mainLayout->addLayout(controlLayout);
    
    // Buffer display
    QLabel *bufferLabel = new QLabel("Buffer:", this);
    mainLayout->addWidget(bufferLabel);
    
    m_bufferDisplay = new QTextEdit(this);
    m_bufferDisplay->setReadOnly(true);
    m_bufferDisplay->setFont(QFont("Courier", 12));
    m_bufferDisplay->setMaximumHeight(100);
    mainLayout->addWidget(m_bufferDisplay);
    
    // Log display
    QLabel *logLabel = new QLabel("Activity Log:", this);
    mainLayout->addWidget(logLabel);
    
    m_logDisplay = new QTextEdit(this);
    m_logDisplay->setReadOnly(true);
    mainLayout->addWidget(m_logDisplay);
    
    // Start with two threads
    addThread();
    addThread();
}

MainWindow::~MainWindow()
{
    // Clean up threads and workers
    for (int i = 0; i < m_threads.size(); ++i) {
        m_workers[i]->stop();
        m_threads[i]->quit();
        m_threads[i]->wait();
    }
    
    qDeleteAll(m_workers);
    qDeleteAll(m_threads);
    
    // SharedBuffer is deleted automatically as a child of this QObject
}

void MainWindow::addThread()
{
    int id = m_threads.size();
    
    // Don't add more threads than we have characters for
    if (id >= CHARACTERS.size()) {
        logMessage("Maximum number of threads reached");
        return;
    }
    
    // Create a new thread
    QThread *thread = new QThread();
    
    // Create a worker with a specific character
    CharacterWorker *worker = new CharacterWorker(id, CHARACTERS[id], m_buffer, 
                                                m_generateIntervalSpinBox->value());
    worker->moveToThread(thread);
    
    // Connect signals/slots
    connect(thread, &QThread::started, worker, &CharacterWorker::start);
    connect(thread, &QThread::finished, worker, &CharacterWorker::deleteLater);
    
    // Store thread and worker
    m_threads.append(thread);
    m_workers.append(worker);
    
    // Start the thread
    thread->start();
    
    logMessage(QString("Added thread #%1 with character '%2'")
                .arg(id)
                .arg(CHARACTERS[id]));
}

void MainWindow::removeThread()
{
    if (!m_threads.isEmpty()) {
        int id = m_threads.size() - 1;
        
        // Stop the worker
        m_workers[id]->stop();
        
        // Stop and wait for the thread
        m_threads[id]->quit();
        m_threads[id]->wait();
        
        // Delete thread and worker
        delete m_threads.takeLast();
        delete m_workers.takeLast();
        
        logMessage(QString("Removed thread #%1").arg(id));
    }
}

void MainWindow::updateGenerateInterval(int ms)
{
    // Update interval for all workers
    for (auto worker : m_workers) {
        worker->setInterval(ms);
    }
    logMessage(QString("Changed generation interval to %1 ms").arg(ms));
}

void MainWindow::updatePopInterval(int ms)
{
    // Update pop interval
    m_buffer->setPopInterval(ms);
    logMessage(QString("Changed pop interval to %1 ms").arg(ms));
}

void MainWindow::updateBufferDisplay(const QString &buffer)
{
    m_bufferDisplay->setText(buffer);
}

void MainWindow::logCharacterAdded(int threadId, QChar c)
{
    logMessage(QString("Thread #%1 added: '%2'").arg(threadId).arg(c));
}

void MainWindow::logCharacterPopped(QChar c)
{
    logMessage(QString("Popped: '%1'").arg(c));
}

void MainWindow::logMessage(const QString &message)
{
    m_logDisplay->append(message);
}
