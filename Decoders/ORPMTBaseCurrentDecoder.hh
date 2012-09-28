// ORPMTBaseCurrentDecoder

#ifndef _ORPMTBaseCurrentDecoder_hh_
#define _ORPMTBaseCurrentDecoder_hh_

#include "ORVDataDecoder.hh"
#include <string>

class ORPMTBaseCurrentDecoder : public ORVDataDecoder
{
  public:
    ORPMTBaseCurrentDecoder() {}
    virtual ~ORPMTBaseCurrentDecoder() {}

    virtual inline UInt_t CrateOf(UInt_t* record)
        { return record[1]; }

    virtual inline UInt_t CardOf(UInt_t* /*record*/)
        { return 0; }

    virtual inline UInt_t CrateNum(UInt_t* record)
        { return record[1]; }

    virtual inline UInt_t SlotMask(UInt_t* record)
        { return record[2]; }

    virtual inline UInt_t ChannelMaskForSlot(UInt_t slot, UInt_t* record)
        { return record[3 + slot]; }

    virtual inline UInt_t ErrorFlags(UInt_t* record)
        { return record[19]; }

    virtual inline UChar_t ADCForSlotAndChannel(UInt_t slot, UInt_t channel, UInt_t* record)
        { return ((UChar_t*)&record[20])[slot*32 + channel]; }

    virtual inline UChar_t BusyForSlotAndChannel(UInt_t slot, UInt_t channel, UInt_t* record)
        { return ((UChar_t*)&record[20 + 16*8])[slot*32 + channel]; }

    virtual const char* TimeStamp(UInt_t* record)
        { return (const char*) (record + 20 + 2*16*8); }

    virtual void Swap(UInt_t* dataRecord);
    virtual const std::string ToJson(UInt_t* record);

    virtual std::string GetDataObjectPath()
        { return "ORXL3Model:Xl3PmtBaseCurrent"; }
};

#endif

