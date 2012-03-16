#ifndef _ORSNOPackedEventProcessor_hh_
#define _ORSNOPackedEventProcessor_hh_

#include "ORCompoundDataProcessor.hh"
#include "ORMTCDecoder.hh"
#include "ORPMTDecoder.hh"
#include "ORCMOSDecoder.hh"
#include "ORRunDecoder.hh"
#include "ORCaen1720Decoder.hh"
#include "ORFIFODecoder.hh"

class ORSNOPackedEventProcessor : public ORCompoundDataProcessor
{
  public:
    ORSNOPackedEventProcessor(std::string label = "SNOPackedFile.root");
    virtual ~ORSNOPackedEventProcessor();
    virtual EReturnCode StartRun();
    virtual EReturnCode ProcessDataRecord(UInt_t* record);
    virtual EReturnCode EndRun();

  protected:
	ORMTCDecoder		fMTCDecoder;
	ORCMOSDecoder		fCMOSDecoder;
	ORPMTDecoder		fPMTDecoder;
	ORCaen1720Decoder	fCaenDecoder;
	ORRunDecoder		fRunDecoder;
	ORFIFODecoder		fFIFODecoder;

	UInt_t fMTCDataId; 
	UInt_t fPMTDataId; 
	UInt_t fCaenDataId; 
	UInt_t fCMOSDataId;
	UInt_t fRunId;
	UInt_t fFIFODataId;

	ORDataProcessor* fMTCProcessor;
	ORDataProcessor* fPMTProcessor;
	ORDataProcessor* fCMOSProcessor;
	ORDataProcessor* fCaenProcessor;
	ORDataProcessor* fRunProcessor;
	ORDataProcessor* fFIFOProcessor;

	UInt_t aRecord;					//pointer into the temporary storage
};

#endif

