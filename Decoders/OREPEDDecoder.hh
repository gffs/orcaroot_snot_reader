// OREPEDDecoder.hh

#ifndef _OREPEDDecoder_hh_
#define _OREPEDDecoder_hh_

#include "ORVDataDecoder.hh"

class OREPEDDecoder : public ORVDataDecoder
{
    public:
    OREPEDDecoder() {}
    virtual ~OREPEDDecoder() {}

    virtual inline UInt_t CrateOf(UInt_t* record)
        { return record[1]; } //0

    virtual inline UInt_t CardOf(UInt_t* /*record*/)
        { return 0; }

    virtual inline UInt_t CrateNum(UInt_t* record)
        { return record[1]; } //0

    virtual inline UInt_t CoarseDelay(UInt_t* record)
        { return record[2]; }

    virtual inline UInt_t FineDelay(UInt_t* record)
        { return record[3]; }

    virtual inline UInt_t ChargePulseAmp(UInt_t* record)
        { return record[4]; }

    virtual inline UInt_t PedestalWidth(UInt_t* record)
        { return record[5]; }

    virtual inline UInt_t CalType(UInt_t* record)
        { return record[6]; }

    virtual inline UInt_t StepNumber(UInt_t* record)
        { return record[7]; }

    virtual const std::string ToJson(UInt_t* record);

    virtual std::string GetDataObjectPath()
        { return "SNOPModel:snopEpedBundle"; }
};

#endif

