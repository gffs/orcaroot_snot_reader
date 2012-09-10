// ORFECVltDecoder.hh

#ifndef _ORFECVltDecoder_hh_
#define _ORFECVltDecoder_hh_

#include "ORVDataDecoder.hh"

class ORFECVltDecoder : public ORVDataDecoder
{
    public:
    ORFECVltDecoder() {}
    virtual ~ORFECVltDecoder() {}

    virtual inline UInt_t CrateOf(UInt_t* record)
        { return record[1]; }

    virtual inline UInt_t CardOf(UInt_t* record)
        { return record[2]; }

    virtual inline UInt_t CrateNum(UInt_t* record)
        { return record[1]; }

    virtual inline UInt_t SlotNum(UInt_t* record)
        { return record[2]; }

    virtual inline Float_t VoltageForIndex(UInt_t idx, UInt_t* record)
        { return *(Float_t*)&record[3+idx]; }

    virtual const char* TimeStamp(UInt_t* record)
        { return (const char*) (record + 24); }

    virtual void Swap(UInt_t* dataRecord);
    virtual const std::string ToJson(UInt_t* record);

    virtual std::string GetDataObjectPath()
        { return "ORXL3Model:FecVlt"; }
};

#endif

