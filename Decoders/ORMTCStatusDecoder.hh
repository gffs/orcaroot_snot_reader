// ORMTCStatusDecoder.hh

#ifndef _ORMTCStatusDecoder_hh_
#define _ORMTCStatusDecoder_hh_

#include "ORVDataDecoder.hh"

class ORMTCStatusDecoder : public ORVDataDecoder
{
    public:
    ORMTCStatusDecoder() {}
    virtual ~ORMTCStatusDecoder() {}

    virtual inline UInt_t CrateOf(UInt_t* record)
        { return record[1]; } //0

    virtual inline UInt_t CardOf(UInt_t* /*record*/)
        { return 0; }

    virtual inline UInt_t CrateNum(UInt_t* record)
        { return record[1]; } //0

    virtual inline UInt_t GTID(UInt_t* record)
        { return record[2] & 0xffffff; }

    virtual inline ULong64_t Cnt10MHz(UInt_t* record)
        { return (ULong64_t)(record[3] + ((record[4] & 0x1fffffULL) << 32)); }

    virtual const std::string Time10MHz(UInt_t* record);

    virtual inline bool DataAvailable(UInt_t* record)
        { return ((record[5] & 0x00800000) == 0)? true: false; }

    virtual inline UInt_t ReadPointer(UInt_t* record)
        { return record[5] & 0xfffff; }

    virtual inline UInt_t WriteNextPointer(UInt_t* record)
        { return record[6] & 0xfffff; }

    virtual inline UInt_t NumRecordsInMem(UInt_t* record);

    virtual const std::string ToJson(UInt_t* record);

    virtual std::string GetDataObjectPath()
        { return "ORMTCModel:MTCStatus"; }
};

#endif

