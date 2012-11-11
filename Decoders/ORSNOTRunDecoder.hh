// ORSNOTRunDecoder.hh

#ifndef _ORSNOTRunDecoder_hh_
#define _ORSNOTRunDecoder_hh_

#include "ORRunDecoder.hh"
#include "ORVDataDecoder.hh"

class ORSNOTRunDecoder : public ORRunDecoder
{
    public:
    ORSNOTRunDecoder() {}
    virtual ~ORSNOTRunDecoder() {}

    virtual const std::string ToJson(UInt_t* record, UInt_t runNumber, UInt_t subrunNumber);
};

#endif

