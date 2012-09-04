#ifndef _ORSNOPackedEventProcessor_hh_
#define _ORSNOPackedEventProcessor_hh_

#include "ORCompoundDataProcessor.hh"
#include "ORMTCDecoder.hh"
#include "ORPMTDecoder.hh"
#include "ORCMOSDecoder.hh"
#include "ORRunDecoder.hh"
#include "ORCaen1720Decoder.hh"
#include "ORFIFODecoder.hh"
#include "ORPMTBaseCurrentDecoder.hh"

#include <zmq.hpp>

class ORSNOPackedEventProcessor : public ORCompoundDataProcessor
{
  public:
    ORSNOPackedEventProcessor(std::string label = "snot_packed.root");
    virtual ~ORSNOPackedEventProcessor();
    virtual EReturnCode StartRun();
    virtual EReturnCode ProcessDataRecord(UInt_t* record);
    virtual EReturnCode EndRun();

  protected:
    ORMTCDecoder fMTCDecoder;
    ORCMOSDecoder fCMOSDecoder;
    ORPMTDecoder fPMTDecoder;
    ORCaen1720Decoder fCaenDecoder;
    ORRunDecoder fRunDecoder;
    ORFIFODecoder fFIFODecoder;
    ORPMTBaseCurrentDecoder fPMTBaseCurrentDecoder;

    UInt_t fMTCDataId; 
    UInt_t fPMTDataId; 
    UInt_t fCaenDataId; 
    UInt_t fCMOSDataId;
    UInt_t fRunId;
    UInt_t fFIFODataId;
    UInt_t fPMTBaseCurrentDataId;

    ORDataProcessor* fMTCProcessor;
    ORDataProcessor* fPMTProcessor;
    ORDataProcessor* fCMOSProcessor;
    ORDataProcessor* fCaenProcessor;
    ORDataProcessor* fRunProcessor;
    ORDataProcessor* fFIFOProcessor;
    ORDataProcessor* fPMTBaseCurrentProcessor;

    zmq::context_t* context;
    zmq::socket_t* socket_json;
};

#endif

