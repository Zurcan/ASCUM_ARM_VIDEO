#ifndef DATAINTERPRETATOR_H
#define DATAINTERPRETATOR_H
#include <QString>

class TMIinterpretator
{

private:

    public:
       //#define vUint8 = 0;
       static const char vUInt8            =0;                             //byte unsigned
       static const char vInt8             =1;                             //byte signed
       static const char vInt16            =2;                             //word signed
       static const char vUInt16           =3;                             //word unsigned
       static const char vInt32            =4;                             //double word signed
       static const char vFract8           =5;                             //numeric similiar as 25.5. Precision assigned by mask.
       static const char vFract16          =6;                             //numeric similiar as 6553.5. Precision assigned by mask.
       static const char vFloat            =7;                             //numeric float
       static const char vFlag             =8;                             //flag.1bit. Setting by mask
       static const char vList             =9;                             //optional element
       static const char vTime             =10;                            //time.32bit.Variable of time
       static const char vProc             =11;                            //subprogram
       static const char vAdjustProc       =12;                            //subprogram, executing with data, has a preamble as submenu
       static const char vSub              =13;                            //submenu
       static const char vString           =14;                            //string up to 255 symbols
       static const char vHString          =15;                            //hidden string
       static const char vText             =16;                            //multi-string text
       static const char vFlag8            =17;                            //flag
       static const char vFlag16           =18;                            //flag
       static const char mUnit             =19;                            //measurement units
       static const char vSettingsProc     =20;                            //procedure of settings adjust processing
       static const char vDropDown         =21;
       static const char vDivider          =22;
       static const char vSerial           =23;
       static const char vSystemProc       =24;
       static const char vVersion          =25;
       static const char vButton           =26;
       static const int null               =0;
//       static const long dividers[6]={1,10,100,1000,10000,100000};

    TMIinterpretator();
    typedef char bytearray;
    bytearray *data;

    bool getInterpretedTable(char *buf);
    void setInterpretationTable(char *p, int recCount);
    void setData(char *p);
    long fieldInt(char *fieldData);
    float fieldFloat(char *fieldData);
    char fieldChar(char *fieldData);
    bool fieldFlag(char *fieldData, char *mask);
    char* fieldString(char *name);
    short int fieldShort(char *fieldData);
    double fieldDouble(char *fieldData);
    QString fieldDropDown(char *fieldData, QString name);
    //fieldTime()
    long getTMITyp(char *name);
    char* createInterpreter();
    char* createSegment(long size);
    int interpreterRecordsCount;

    enum eventType{ErrorLog=0, UserMessage=1, SystemMessage=2, endOfEventType=3};
    enum eventCode{Code1=0, Code2=1, Code3=2, Code4=3, endOfEventCode=4};

//#pragma pack (push,1)
  struct TInterpItem_t
    {
        char level ;
        char name[32] ;
        short int offset ;
        short int sigDescr ;
        char mask_ ;
        long min ;
        long max ;
        long defaultVal ;
        long typ;
  } __attribute__ ((packed)) ;
// #pragma pack (pop)
    TInterpItem_t TInterpItem;
    TInterpItem_t setupMenu[7];
//#pragma pack (push,1)
 TInterpItem_t TInterpItemArray[50]; //__attribute__((packed));
//#pragma pack (pop)

    TInterpItem_t *PointerTInterpItemArray;
    int lastItem,itemCount;

   ~TMIinterpretator();
};

#endif // DATAINTERPRETATOR_H
