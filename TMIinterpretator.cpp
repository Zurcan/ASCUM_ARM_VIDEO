#include "TMIinterpretator.h"
//#include "dos.h"
#include "stdio.h"
//#include "alloc.h"
//#include <QVector>
#include <float.h>
#include <malloc.h>
TMIinterpretator::TMIinterpretator()
{
    lastItem=0;
    itemCount=0;
}

void TMIinterpretator::setInterpretationTable(char *p, int recCount)
{

    //TInterpItem_t *TmpPointer = TInterpItemArray;
    //TmpPointer->level = *p;
//    PointerTInterpItemArray = &TInterpItemArray[0];
    PointerTInterpItemArray = (TInterpItem_t*)p;
    for(int i = 0; i<recCount; i++)
        TInterpItemArray[i]=*PointerTInterpItemArray++;
    // = p;



}

long const dividers[6]={1,10,100,1000,10000,100000};
bool TMIinterpretator::getInterpretedTable(char *buf)
{

    return true;
}

void TMIinterpretator::setData(char *p)
{
    data = p;
}

long TMIinterpretator::getTMITyp(char *name)
{
    return 0;
}

char TMIinterpretator::fieldChar(char *fieldData)
{
    char *retVal;
    retVal = ((char*)fieldData);
    return *retVal;
}

short int TMIinterpretator::fieldShort(char *fieldData)
{
    short int *retVal;
    retVal = ((short int*)fieldData);
    return *retVal;
}
long TMIinterpretator::fieldInt(char *fieldData)
{
    unsigned int *retVal;
    retVal = ((unsigned int*)fieldData);
    return *retVal;
    //TInterpItem_t it;
//    int i;
//    char *result;
//    TInterpItem_t *tmpItem;
//    tmpItem->name[0] = *name;
//    if(tmpItem!=null)
//        switch (tmpItem->typ)
//        {
//        case vUInt8: return (long)(data+tmpItem->offset);
//            break;
//        case vInt8: return (long)(data+tmpItem->offset);
//            break;
//        case vInt16: return (long)(data+tmpItem->offset);
//            break;
//        case vUInt16: return (long)(data+tmpItem->offset);
//            break;
//        case vInt32: return(long)(data+tmpItem->offset);
//            break;
//        default: return 0xffff;
//        }
//    else return 0xffff;
//    return 0xffff;
}

float TMIinterpretator::fieldFloat(char *fieldData)
{
    float *retVal;
    retVal = ((float*)fieldData);
    return *retVal;
//    TInterpItem_t *tmpItem;
//    tmpItem->name[0] = *name;
//    if(tmpItem!=null)
//        switch(tmpItem->typ)
//        {
//        case vFract8: return (float)((int)(data+tmpItem->offset)/dividers[tmpItem->mask_]);
//            break;
//        case vFract16: return (float)((int)(data+tmpItem->offset)/dividers[tmpItem->mask_]);
//            break;
//        case vFloat: return (float)((int)(data+tmpItem->offset));
//            break;
//        default: return null;
//        break;
//        }
//    else return null;
//    return null;
}

double TMIinterpretator::fieldDouble(char *fieldData)
{
    double *retVal;
    retVal = ((double*)fieldData);
    return *retVal;
}

bool TMIinterpretator::fieldFlag(char *fieldData, char *mask)
{
    char retVal;
    retVal = *fieldData & *mask;
    //if(*retVal%3==0)return false;
    return retVal;
}

QString TMIinterpretator::fieldDropDown(char *fieldData, QString name)
{
    long *retVal;
    retVal = ((long*)fieldData);
    if(name =="Тип события")
    {
        switch (*retVal)
        {
            case 0:
            {
            return "Ошибки";
            break;
            }
            case 1:
            {
            return "Пользовательские";
            break;
            }
            case 2:
            {
            return "Системные";
            break;
            }
            default:
            {
            return "noSuchEventType";
            break;
            }
        }
    }
    if(name =="Код события")
        {
            switch (*retVal)
            {
                case 0:
                {
                return "Код1";
                break;
                }
                case 1:
                {
                return "Код2";
                break;
                }
                case 2:
                {
                return "Код3";
                break;
                }
                case 3:
                {
                return "Код4";
                break;
                }
                default:
                {
                return "noSuchCodeType";
                break;
                }
            }
    }
    return "none";
}

char* TMIinterpretator::createInterpreter()
{

    TInterpItem_t newstruct[7]=
            {
            /****************************************************************************************************************************************************************************************
             Структура системного меню
            *****************************************************************************************************************************************************************************************
            Ур|	Название пункта (31 симв макс					|Адрес ячейки				|Единица|Маска	|Min	|Max	|  Default   | Тип переменной
            пм|	(31 симв. макс для подм, 31 для др)				|или буфера(смещение)		|измерен|       |       |       |
            ****************************************************************************************************************************************************************************************/
            // Задается адресное смещение всей записи настроек, для вычисления внутренних смещений внутри структуры
            {1,   "Время"                                        ,sizeof(int)              ,0      ,0      ,FLT_MIN ,FLT_MAX       ,0         ,vTime	},
            {1,	  "Тип события"                                  ,sizeof(enum eventType)   ,0      ,0      ,ErrorLog,endOfEventType,ErrorLog  ,vDropDown},
            {1,	  "Код события"                                  ,sizeof(enum eventCode)   ,0      ,0      ,Code1   ,endOfEventCode,Code1     ,vDropDown},
            // {1,	  "System state mould"                          ,&rSetup.inHighBitMask	,0      ,0      ,0xFFFF ,0          ,0xFFFF         ,vDropDown},
            {1,	  "Направление дв."                              ,sizeof(int)              ,0      ,0      ,0x0000  ,0x0001        ,0x0000    ,vFlag16},
            {1,	  "Скорость"			                         ,sizeof(float)		       ,0      ,0      ,FLT_MIN ,FLT_MAX       ,0         ,vFloat},
            {1,	  "Частота"                                      ,sizeof(float)            ,0      ,0      ,FLT_MIN ,FLT_MAX       ,0         ,vFloat},
            {1,	  "Давление"                                     ,sizeof(float)            ,0      ,0      ,FLT_MIN ,FLT_MAX       ,0         ,vFloat},
            //{2,	    "Полярность измер.частоты"		                        ,&rSetup.freqPolarity		        ,0	,0      ,0xFFFF ,0      ,0xFFFF      ,vflg16	},
            };
    int tmpLength=sizeof(newstruct[0]);
    for(int i = 0; i<7;i++)
    setupMenu[i]=newstruct[i];
    char *retBuf = &setupMenu[0].level;
    return retBuf;
}

TMIinterpretator::~TMIinterpretator()
{

}
