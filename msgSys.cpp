#include "msgSys.h"
#include "stdlib.h"
#include <QTextCodec>

msgSys::msgSys(QObject *parent) :
    QObject(parent)
{
    messages = NULL;
    lastMsg = 0;
    m_msgs = QList<QObject *>();
}

msgSys::~msgSys()
{
    if (messages)
        free(messages);

    while (!m_msgs.isEmpty())
         delete m_msgs.takeFirst();
}

void msgSys::parseMessages(void *p)
{
    int i;
    int n, k, l, c;
    char type;
    char s[255], text[255], hint[255];
    char langm[255];
    uint16_t w;
    char *m;
    bool lmatch, ml;

    if (p == NULL)
        return;

    if (messages != NULL)
    {
        free(messages);
        messages = NULL;
    }

    m = (char *)p;
    n = k = l = 0; c = 0; s[c] = '\0'; ml = false; lmatch = true;
    for (i = 0; i < 65536; i++)
    {
        if (m[i] != '\'')
        {
            if ( ((m[i] != 13) || (k != 0)) &&
                   m[i] != '\0' )
            {
                if ( m[i] != ',' || k > 0)
                    s[c++] = m[i];
                else
                {
                    s[c++] = '\0';

                    switch (n)
                    {
                    case 0:
                        int t;
                        sscanf(s, "%x",&t);
                        w = (uint16_t)t;
                        break;
                    case 1:
                        type = s[0];
                        break;
                    case 2:
                        strncpy(text,s,c);
                        break;
                    case 3:
                        strncpy(hint,s,c);
                        break;
                    }
                    c = 0; s[c] = '\0';
                    n++;
                }
            }
            else
            {
                s[c++] = '\0';
                strncpy(langm, s, c);
                if (strcmp(langm, "MULTILINGUAL") == 0)
                {
                    lmatch = false;
                    ml = true;
                }
                else if (ml && (strncmp(langm, "LANGUAGE[", 9) == 0))
                {
                    /* Accept only RUSSIAN languages */
                    if (strncmp(langm, "LANGUAGE[RUSSIAN]", 17) == 0)
                        lmatch = true;
                }
                else if (lmatch)
                {
                    n = 0;
                    s[c] = '\0';
                    strncpy(hint,s,c);

                    if (messages == NULL)
                    {
                        messages = (memMessages_t*)malloc(sizeof(memMessage_t) +
                                                                       sizeof(int));
                        messages->count = 0;
                    }
                    else
                    {
                        messages = (memMessages_t*)realloc(messages,
                            sizeof(memMessage_t)*(messages->count+1) + sizeof(int));
                    }
                    messages->message[messages->count].code = w;
                    messages->message[messages->count].type = type;
                    strcpy(messages->message[messages->count].message, text);
                    strcpy(messages->message[messages->count].hint, hint);
                    messages->count++;
                }
                else
                    n = 0;

                c = 0; s[c] = '\0';
            }
        }
        else
            k = 1-k;

        if (m[i] == '\0')
            break;
    }
}

void msgSys::doneMessages()
{
    if (messages)
        free(messages);
}

bool msgSys::findMessage(uint16_t mid, char *type, QString *text, QString *hint)
{
    int i;

    if (messages)
        for (i = 0; i < messages->count; i++)
            if (messages->message[i].code == mid)
            {
                QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
                *type = messages->message[i].type;
                *text = codec->toUnicode(messages->message[i].message);
                *hint = codec->toUnicode(messages->message[i].hint);

                return true;
            }

    *type = 'T';
    *text = "Unknown message";
    *hint = '\0';

    return false;   /* message not found */
}

int msgSys::findMessage(uint16_t mid)
{
    int i;

    if (messages)
        for (i = 0; i < messages->count; i++)
            if (messages->message[i].code == mid)
                return i;

    return -1;
}

void msgSys::addMessage(MessageHeader_t *msg)
{
    char type;
    QString text, hint;

//    qDebug("code: %d\ncounter: %d", msg->code, msg->messageCounter);
    if (lastMsg != msg->messageCounter){
        lastMsg = msg->messageCounter;

        if (findMessage(msg->code,&type,&text,&hint))
        {
    //        qDebug("type: %c\ntext: \"%s\"\nhint: \"%s\"\n", type, text.toAscii().data(),
    //                                     hint.toAscii().data());
            if (m_msgs.count() >= 5)
                delete m_msgs.takeLast();

            m_msgs.prepend(new MsgObject(type,text,hint));
            emit msgsChanged(m_msgs);
            emit newMessage(type, text, hint);
        }
    }
}
