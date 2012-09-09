// ORXL3VltDecoder.hh

#ifndef _ORXL3VltDecoder_hh_
#define _ORXL3VltDecoder_hh_

#include "ORVDataDecoder.hh"

class ORXL3VltDecoder : public ORVDataDecoder
{
    public:
    ORXL3VltDecoder() {}
    virtual ~ORXL3VltDecoder() {}

    virtual inline UInt_t CrateOf(UInt_t* record)
        { return record[1]; }

    virtual inline UInt_t CardOf(UInt_t* /*record*/)
        { return 0; }

    virtual inline UInt_t CrateNum(UInt_t* record)
        { return record[1]; }

    virtual inline Float_t VoltageForIndex(UInt_t idx, UInt_t* record)
        { return *(Float_t*)&record[2+idx]; }

    virtual const char* TimeStamp(UInt_t* record)
        { return (const char*) (record + 10); }

    virtual void Swap(UInt_t* dataRecord);
    virtual const std::string ToJson(UInt_t* record);

    virtual std::string GetDataObjectPath()
        { return "ORXL3Model:Xl3Vlt"; }
};

#endif

