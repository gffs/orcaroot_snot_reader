// ORCMOSDecoder.hh

#ifndef _ORCMOSDecoder_hh_
#define _ORCMOSDecoder_hh_

#include "ORVDataDecoder.hh"

class ORCMOSDecoder : public ORVDataDecoder
{
  public:
    ORCMOSDecoder() {}
    virtual ~ORCMOSDecoder() {}

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

	virtual inline UInt_t Delay(UInt_t* record)
		{ return record[19]; }
	
	virtual inline UInt_t ErrorFlags(UInt_t* record)
		{ return record[20]; }

	virtual inline Float_t CMOSRateForSlotAndChannel(UInt_t slot, UInt_t channel, UInt_t* record)
		{ return record[21 + slot*32 + channel]; }

	virtual inline Float_t CMOSRateForOffset(UInt_t offset, UInt_t* record)
		{ return record[21 + offset]; }

	virtual std::string GetDataObjectPath()
		{ return "ORXL3Model:Xl3CmosRate"; }
};

#endif

