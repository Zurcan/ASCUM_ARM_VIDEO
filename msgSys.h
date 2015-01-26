#ifndef MSGSYS_H
#define MSGSYS_H

#include <QObject>
#include <ints.h>
#include <QQueue>

struct MessageHeader_t {
    uint16_t code;
    int32_t messageCounter;
};

struct __attribute__((packed)) memMessage_t {
    uint16_t code;
    char type;
    char message[256];
    char hint[256];
};

struct __attribute__((packed)) memMessages_t {
    int count;
    memMessage_t message[65536];
};

class MsgObject : public QObject
{
     Q_OBJECT

     Q_PROPERTY(char type READ type WRITE setType /*NOTIFY typeChanged*/)
     Q_PROPERTY(QString text READ text WRITE setText /*NOTIFY textChanged*/)
     Q_PROPERTY(QString hint READ hint WRITE setHint /*NOTIFY hintChanged*/)

public:
    explicit MsgObject(char type, QString  &text, QString &hint) : QObject() {
        m_type = type; m_text = text; m_hint = hint;
    }
    MsgObject(QObject *parent = 0) : QObject(parent) {;}

    char type() const { return m_type; }
    void setType(char type) { m_type = type; }

    const QString & text() const { return m_text; }
    void setText(QString & text) { m_text = text; }

    const QString & hint() const { return m_hint; }
    void setHint(QString & hint) { m_hint = hint; }

private:
    char m_type;
    QString m_text;
    QString m_hint;
};

class msgSys : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject *> msgs READ msgs WRITE setMsgs NOTIFY msgsChanged)

public:
    explicit msgSys(QObject *parent = 0);
    ~msgSys();

    void parseMessages(void *rawMsgs);
    bool findMessage(uint16_t mid, char *type, QString *text, QString *hint);
    int findMessage(uint16_t mid);
    void doneMessages();
    void addMessage(MessageHeader_t *msg);

    QList<QObject *> msgs() const { return m_msgs; }
    void setMsgs(QList<QObject *> msgs) { m_msgs = msgs; emit msgsChanged(msgs);}

    memMessages_t *messages;
    
signals:
    void newMessage(char type, QString message, QString hint);
    void msgsChanged(QList<QObject *> msgs);
    
public slots:

private:
    int lastMsg;
    QList<QObject *> m_msgs;

};

#endif // MSGSYS_H
