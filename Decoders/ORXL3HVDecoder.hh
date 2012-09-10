// ORXL3HVDecoder.hh

#ifndef _ORXL3HVDecoder_hh_
#define _ORXL3HVDecoder_hh_

#include "ORVDataDecoder.hh"

class ORXL3HVDecoder : public ORVDataDecoder
{
    public:
    ORXL3HVDecoder() {}
    virtual ~ORXL3HVDecoder() {}

    virtual inline UInt_t CrateOf(UInt_t* record)
        { return record[1]; }

    virtual inline UInt_t CardOf(UInt_t* /*record*/)
        { return 0; }

    virtual inline UInt_t CrateNum(UInt_t* record)
        { return record[1]; }

    virtual inline Float_t VoltageA(UInt_t* record)
        { return *(Float_t*)&record[2]; }

    virtual inline Float_t VoltageB(UInt_t* record)
        { return *(Float_t*)&record[3]; }

    virtual inline Float_t CurrentA(UInt_t* record)
        { return *(Float_t*)&record[4]; }

    virtual inline Float_t CurrentB(UInt_t* record)
        { return *(Float_t*)&record[5]; }

    virtual const char* TimeStamp(UInt_t* record)
        { return (const char*) (record + 6); }

    virtual void Swap(UInt_t* dataRecord);
    virtual const std::string ToJson(UInt_t* record);

    virtual std::string GetDataObjectPath()
        { return "ORXL3Model:Xl3Hv"; }
};

#endif

