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