// ORFIFODecoder.hh

#ifndef _ORFIFODecoder_hh_
#define _ORFIFODecoder_hh_

#include "ORVDataDecoder.hh"

class ORFIFODecoder : public ORVDataDecoder
{
	public:
	ORFIFODecoder() {}
	virtual ~ORFIFODecoder() {}

	virtual inline UInt_t CrateOf(UInt_t* record)
		{ return record[1]; }

	virtual inline UInt_t CardOf(UInt_t* /*record*/)
		{ return 0; }

	virtual inline UInt_t CrateNum(UInt_t* record)
		{ return record[1]; }

	virtual inline Float_t FIFOForSlot(UInt_t slot, UInt_t* record)
		{ return record[2 + slot]; }

	virtual std::string GetDataObjectPath()
		{ return "ORXL3Model:Xl3Fifo"; }
};

#endif

