#ifndef _ORSNOPackedEventProcessor_hh_
#define _ORSNOPackedEventProcessor_hh_

#include "ORCompoundDataProcessor.hh"
#include "ORMTCDecoder.hh"
#include "ORMTCStatusDecoder.hh"
#include "ORPMTDecoder.hh"
#include "ORCMOSDecoder.hh"
#include "ORRunDecoder.hh"
#include "ORSNOTRunDecoder.hh"
#include "ORCaen1720Decoder.hh"
#include "ORFIFODecoder.hh"
#include "ORPMTBaseCurrentDecoder.hh"
#include "ORXL3HVDecoder.hh"
#include "ORXL3VltDecoder.hh"
#include "ORFECVltDecoder.hh"
#include "OREPEDDecoder.hh"
#include "ORRHDRDecoder.hh"

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
    ORMTCStatusDecoder fMTCStatusDecoder;
    ORCMOSDecoder fCMOSDecoder;
    ORPMTDecoder fPMTDecoder;
    ORCaen1720Decoder fCaenDecoder;
    ORSNOTRunDecoder fRunDecoder;
    ORFIFODecoder fFIFODecoder;
    ORPMTBaseCurrentDecoder fPMTBaseCurrentDecoder;
    ORXL3HVDecoder fXL3HVDecoder;
    ORXL3VltDecoder fXL3VltDecoder;
    ORFECVltDecoder fFECVltDecoder;
    OREPEDDecoder fEPEDDecoder;
    ORRHDRDecoder fRHDRDecoder;

    UInt_t fMTCDataId; 
    UInt_t fMTCStatusDataId; 
    UInt_t fPMTDataId; 
    UInt_t fCaenDataId; 
    UInt_t fCMOSDataId;
    UInt_t fRunId;
    UInt_t fFIFODataId;
    UInt_t fPMTBaseCurrentDataId;
    UInt_t fXL3HVDataId;
    UInt_t fXL3VltDataId;
    UInt_t fFECVltDataId;
    UInt_t fEPEDDataId;
    UInt_t fRHDRDataId;

    ORDataProcessor* fMTCProcessor;
    ORDataProcessor* fMTCStatusProcessor;
    ORDataProcessor* fPMTProcessor;
    ORDataProcessor* fCMOSProcessor;
    ORDataProcessor* fCaenProcessor;
    ORDataProcessor* fRunProcessor;
    ORDataProcessor* fFIFOProcessor;
    ORDataProcessor* fPMTBaseCurrentProcessor;
    ORDataProcessor* fXL3HVProcessor;
    ORDataProcessor* fXL3VltProcessor;
    ORDataProcessor* fFECVltProcessor;
    ORDataProcessor* fEPEDProcessor;
    ORDataProcessor* fRHDRProcessor;

    zmq::context_t* context;
    zmq::socket_t* socket_json;
};

#endif

