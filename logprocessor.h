#ifndef LOGPROCESSOR_H
#define LOGPROCESSOR_H
#include <QString>
//#include <QTextStream>
#include <QFile>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
#include <QVector>
class logProcessor
{
   // Q_OBJECT
private:
    /*
     *This class can give to user ability to operate with log file. Log file dismembers registrator log file into logical parts,
     *Full log file structure is drawed below:
                                                                ___________
                                                                /fileHeader  /      --------> contains information about file (look at structure)
                                                         ___/__________/___
                                                      / /S / segment1Header  /   -------> contains information about segment (look structure)
                                                      | /E / __ __ __ __ __    /
                                                      | /G /   record1            /   -------> segment consists of records, and there could be a plenty of records
                                                      | /M /__ __ __ __ __     /
                  and file from segments <----| /E /   record2             /
                                                      | /N /__ __ __ __ __     /
                                                      | /T   .........                 /
                                                      | /1                           /
                                                      \ /__________________/
                                                        /S / segment2Header /
                                                        /E / __ __ __ __ __   /
                                                        /G /   record1           /
                                                        /M /__ __ __ __ __    /
                                                        /E /   record2           /
                                                        /N /__ __ __ __ __    /
                                                        /T   .........                /
                                                        /2                          /
                                                        /__________________/

     */

    QString FileName;
    int globalVectIterator;
public:
    QFile tmpFile;
    logProcessor();
    qint64 logDataPointer;
    QVector <long> segIDs;
    int selectLogFile(QString filename);
    long selectSegment(long ID);              //ID = typedCode||interpFlg;
    int checkSegmentsExistance();
    bool readSegment(char *buf,int size);
    bool seekRecord(long ID, int recCount);
    bool readRecord(int recCount, int Size, int savedDataPointer);
    bool CRC32checker(char *buf, int CRC, int length);
    int CRC32calculator(char *buf, long length);
    int checkSegmentCRC32(long ID);
    unsigned long CRC32updater(char *buf, int length, unsigned long crc);
    bool readFileHeader();
    bool readTMIInterpreter(char *buf);
    char* generateFileHeader();
    char* generateSegmentHeader(char* buf);
    long readTmpID(long pointer);
    long readSegmentSize(long pointer);//reads size of segment
    bool moveBackLDPtr(); // moves value to beginning of block if true, else not moves
    bool setValueLDPtr(qint64); // sets value to logDataPointer
    bool pointFileValAtLDPtr(long);//points value to l
    bool clearBuff();
    long setTmpID();
//#pragma pack (push,1)
  struct segmentHeader_t{
        long ID;
        long size;                              //segment size in bytes
        long recordSize;                        //record size in bytes
        long CRC32;
        long reserved[48];
    };//__attribute__((packed));
//#pragma pack (pop)
    long logRecordPointer;
    char record[100];//for our log
    char *bufferredSegment;
    char *bufferredRecord;
    #define SIZE_OF_FILEHEADER 40
    #define SIZE_OF_SEGMENTHEADER 208
    #define SEG_QTY 5
    #define idf_InterpretationData                  0x80000000
 //   #pragma pack (push,1)
    struct fileHeader_t{
        char askumLog[8];                       //"ASKUMLOG"
        char formatVersion;                     // =0
        char pad[3];
        long reserved[4];                       // =0
        long segmentsCount;                     //
        long fileSize;                          //
        long CRC32;                             //
    };//__attribute__((packed));
 //   #pragma pack (pop)
    segmentHeader_t segmentHeader;
    segmentHeader_t segmenHeaderCRC;
    fileHeader_t fileHeader;
    struct fileHeader_t *fileHeaderPointer;
    struct segmentHeader_t *segmentHeaderPointer;
   ~logProcessor();
};

#endif // LOGPROCESSOR_H
