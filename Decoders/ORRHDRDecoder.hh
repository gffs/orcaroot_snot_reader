// ORRHDRDecoder.hh

#ifndef _ORRHDRDecoder_hh_
#define _ORRHDRDecoder_hh_

#include "ORVDataDecoder.hh"

class ORRHDRDecoder : public ORVDataDecoder
{
    public:
    ORRHDRDecoder() {}
    virtual ~ORRHDRDecoder() {}

    virtual inline UInt_t CrateOf(UInt_t* record)
        { return record[1]; } //0

    virtual inline UInt_t CardOf(UInt_t* /*record*/)
        { return 0; }

    virtual inline UInt_t CrateNum(UInt_t* record)
        { return record[1]; } //0

    virtual inline UInt_t Date(UInt_t* record)
        { return record[2]; }

    virtual inline UInt_t Time(UInt_t* record)
        { return record[3]; }
 
    virtual inline UInt_t DaqCodeVersion(UInt_t* record)
        { return record[4]; }

    virtual inline UInt_t RunNumber(UInt_t* record)
        { return record[5]; }

    virtual inline UInt_t CalibrationTrialNumber(UInt_t* record)
        { return record[6]; }

    virtual inline UInt_t SourceMask(UInt_t* record)
        { return record[7]; }

    virtual inline ULong64_t RunMask(UInt_t* record)
        { return (ULong64_t)(record[8] + ((ULong64_t)(record[12])) << 32); }

    virtual inline UInt_t GtCrateMask(UInt_t* record)
        { return record[9]; 
}
    virtual const std::string ToJson(UInt_t* record);

    virtual std::string GetDataObjectPath()
        { return "SNOPModel:snopRhdrBundle"; }
};

#endif

