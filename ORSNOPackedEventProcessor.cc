// ORSNOPackedEventProcessor.cc

#include "ORSNOPackedEventProcessor.hh"
#include "ORRunContext.hh"
#include "ORLogger.hh"
#include "ORUtils.hh"
#include <iostream>

using namespace std;

ORSNOPackedEventProcessor::ORSNOPackedEventProcessor(std::string /*label*/)
{
    SetComponentBreakReturnsFailure();

    fMTCProcessor = new ORDataProcessor(&fMTCDecoder);
    AddProcessor(fMTCProcessor);

    fMTCStatusProcessor = new ORDataProcessor(&fMTCStatusDecoder);
    AddProcessor(fMTCStatusProcessor);

    fPMTProcessor = new ORDataProcessor(&fPMTDecoder);
    AddProcessor(fPMTProcessor);

    fCMOSProcessor = new ORDataProcessor(&fCMOSDecoder);
    AddProcessor(fCMOSProcessor);

    fCaenProcessor = new ORDataProcessor(&fCaenDecoder);
    AddProcessor(fCaenProcessor);

    fRunProcessor = new ORDataProcessor(&fRunDecoder);
    AddProcessor(fRunProcessor);

    fFIFOProcessor = new ORDataProcessor(&fFIFODecoder);
    AddProcessor(fFIFOProcessor);

    fPMTBaseCurrentProcessor = new ORDataProcessor(&fPMTBaseCurrentDecoder);
    AddProcessor(fPMTBaseCurrentProcessor);

    fXL3HVProcessor = new ORDataProcessor(&fXL3HVDecoder);
    AddProcessor(fXL3HVProcessor);

    fXL3VltProcessor = new ORDataProcessor(&fXL3VltDecoder);
    AddProcessor(fXL3VltProcessor);

    fFECVltProcessor = new ORDataProcessor(&fFECVltDecoder);
    AddProcessor(fFECVltProcessor);

    fEPEDProcessor = new ORDataProcessor(&fEPEDDecoder);
    AddProcessor(fEPEDProcessor);

    fRHDRProcessor = new ORDataProcessor(&fRHDRDecoder);
    AddProcessor(fRHDRProcessor);

    context = new zmq::context_t(1);
    socket_json = new zmq::socket_t(*context, ZMQ_PUB);
    try {
        socket_json->bind("tcp://*:5028");
    }
    catch (zmq::error_t &e) {
        cout << "json PUB socket bind failed with errno: " << e.num();
        cout << ", " << e.what() << endl;
        //exit?
    }
}


ORSNOPackedEventProcessor::~ORSNOPackedEventProcessor()
{
    delete socket_json;
    delete context;

    delete fMTCProcessor;
    delete fMTCStatusProcessor;
    delete fPMTProcessor;
    delete fCMOSProcessor;
    delete fCaenProcessor;
    delete fRunProcessor;
    delete fFIFOProcessor;
    delete fPMTBaseCurrentProcessor;
    delete fXL3HVProcessor;
    delete fXL3VltProcessor;
    delete fFECVltProcessor;
    delete fEPEDProcessor;
    delete fRHDRProcessor;
}


ORDataProcessor::EReturnCode ORSNOPackedEventProcessor::StartRun()
{

    fMTCDataId = fMTCProcessor->GetDataId();
    fMTCStatusDataId = fMTCStatusProcessor->GetDataId();
    fPMTDataId = fPMTProcessor->GetDataId();
    fCMOSDataId = fCMOSProcessor->GetDataId();
    fCaenDataId = fCaenProcessor->GetDataId();
    fRunId = fRunProcessor->GetDataId();
    fFIFODataId = fFIFOProcessor->GetDataId();
    fPMTBaseCurrentDataId = fPMTBaseCurrentProcessor->GetDataId();
    fXL3HVDataId = fXL3HVProcessor->GetDataId();
    fXL3VltDataId = fXL3VltProcessor->GetDataId();
    fFECVltDataId = fFECVltProcessor->GetDataId();
    fEPEDDataId = fEPEDProcessor->GetDataId();
    fRHDRDataId = fRHDRProcessor->GetDataId();

    return kSuccess;
}


ORDataProcessor::EReturnCode ORSNOPackedEventProcessor::EndRun()
{
    return kSuccess;
}


ORDataProcessor::EReturnCode ORSNOPackedEventProcessor::ProcessDataRecord(UInt_t* record)
{
    unsigned int thisDataId = fMTCDecoder.DataIdOf(record); // any long decoder would do the job

    //GetRunContext()->GetRunNumber();
    //GetRunContext()->GetSubRunNumber();

    if (thisDataId == fMTCDataId) {
        ORDataProcessor::EReturnCode code = ORCompoundDataProcessor::ProcessDataRecord(record);
        if (code != kSuccess) return code;
        
        //decode MTC bundle
        //fMTCDecoder.Cnt10Mhz(record);
        //fMTCDecoder.Cnt50Mhz(record);
        //fMTCDecoder.GTId(record);
        //fMTCDecoder.GTMask(record);
        //fMTCDecoder.MissTrg(record);
        //see ORMTCDecoder.hh for other...
    }
    else if (thisDataId == fPMTDataId) {
        //record[0] was swapped by ORVReader
        //record[1] was written by ORCA
        ORUtils::Swap(record[1]);
        //the big endian MegaBundle follows
        fPMTDecoder.Swap(record);

        //the Megabundle was sent by crate
        //fPMTDecoder.CrateOf(record);

        if (fPMTDecoder.RevOf(record) == 0) {
            unsigned int bundle_length = (fPMTDecoder.LengthOf(record) - 2) / 3;
            record += 2;
            for (; bundle_length != 0; bundle_length--) {
                //decode PMT bundle
                //fPMTDecoder.GTId(record);
                //fPMTDecoder.Crate(record);
                //fPMTDecoder.Card(record);
                //fPMTDecoder.Channel(record);
                //fPMTDecoder.Cell(record);
                //fPMTDecoder.CGT16(record);
                //fPMTDecoder.CGT24(record);
                //fPMTDecoder.ES16(record);
                //fPMTDecoder.Missed(record);
                //fPMTDecoder.NC(record);
                //fPMTDecoder.LGI(record);
                //fPMTDecoder.QHL(record);
                //fPMTDecoder.QHS(record);
                //fPMTDecoder.QLX(record);
                //fPMTDecoder.TAC(record);
                //see ORPMTDecoder for rest
                record += 3;
            }
        }
        else {
            //new MegaBundle with miniBundles
        }
    }
    else if (thisDataId == fCaenDataId) {
        ORDataProcessor::EReturnCode code = ORCompoundDataProcessor::ProcessDataRecord(record);
        if (code != kSuccess) return code;

        //decode Caen bundle
        //fCaenDecoder.EventCount(record);
        //fCaenDecoder.ChannelMask(record);
        //fCaenDecoder.Pattern(record);
        //fCaenDecoder.EventCount(record);
        //fCaenDecoder.Clock(record);

        //fCaenDecoder.TraceLength(record, 0);
        record += 6; // 2 ORCA long header + 4 CAEN header

        //the first sample of the first trace is *record
        //see Caen data sheet for details
        //fCaenDecoder.CopyTrace(record, traces[i]->Waveform, numSamples);
        //see ORCaen1720Decoder.hh for rest
    }
    else if (thisDataId == fRunId) {
        ORDataProcessor::EReturnCode code = ORCompoundDataProcessor::ProcessDataRecord(record);
        if (code != kSuccess) return code;

        const std::string data(fRunDecoder.ToJson(record, GetRunContext()->GetRunNumber(), GetRunContext()->GetSubRunNumber()));
        zmq::message_t msg(data.length());
        memcpy((void*) msg.data(), data.c_str(), data.length());
        socket_json->send(msg);
 
        //builder template follows
        /*
        if (fRunDecoder.IsHeartBeat(record)) {
            cout << "Run HeartBeat obtained" << endl;
            cout << "heartbeat time: " << fRunDecoder.UtimeOf(record) << endl;
            cout << "time to the next heartbeat: " << record[2] << endl;
        }
        else if (fRunDecoder.IsRunStart(record)) {
            cout << "Run Start obtained" << endl;
            if (record[1] & 0x2) cout << "was soft start" << endl;
            if (record[1] & 0x4) cout << "was remote control start" << endl;
            cout << "run start time: " << fRunDecoder.UtimeOf(record) << endl;
        }
        else if (fRunDecoder.IsPrepareForSubRun(record)) {
            cout << "Subrun Stop obtained" << endl;
            cout << "subrun stop time: " << fRunDecoder.UtimeOf(record) << endl;
        }
        else if (fRunDecoder.IsSubRunStart(record)) {
            cout << "Subrun Start obtained" << endl;
            cout << "subrun start time: " << fRunDecoder.UtimeOf(record) << endl;
        }
        else if (fRunDecoder.IsRunStop(record)) {
            cout << "Run End obtained" << endl;
            if (record[1] & 0x2) cout << "soft end" << endl;
            if (record[1] & 0x4) cout << "remote control" << endl;
            cout << "run stop time: " << fRunDecoder.UtimeOf(record) << endl;
        }
        else {
            //some other run record we don't care about
        }
        cout << "run number: " << GetRunContext()->GetRunNumber() << endl;
        cout << "subrun number: " << GetRunContext()->GetSubRunNumber() << endl;
        */
    }
    else if (thisDataId == fCMOSDataId) {
        ORDataProcessor::EReturnCode code = ORCompoundDataProcessor::ProcessDataRecord(record);
        if (code != kSuccess) return code;

        const std::string data(fCMOSDecoder.ToJson(record));
        zmq::message_t msg(data.length());
        memcpy((void*) msg.data(), data.c_str(), data.length());
        socket_json->send(msg);
    }
    else if (thisDataId == fFIFODataId) {
        ORDataProcessor::EReturnCode code = ORCompoundDataProcessor::ProcessDataRecord(record);
        if (code != kSuccess) return code;

        const std::string data(fFIFODecoder.ToJson(record));
        zmq::message_t msg(data.length());
        memcpy((void*) msg.data(), data.c_str(), data.length());
        socket_json->send(msg);
    }
    else if (thisDataId == fPMTBaseCurrentDataId) {
        ORDataProcessor::EReturnCode code = ORCompoundDataProcessor::ProcessDataRecord(record);
        if (code != kSuccess) return code;

        const std::string data(fPMTBaseCurrentDecoder.ToJson(record));
        zmq::message_t msg(data.length());
        memcpy((void*) msg.data(), data.c_str(), data.length());
        socket_json->send(msg);
    }
    else if (thisDataId == fXL3HVDataId) {
        ORDataProcessor::EReturnCode code = ORCompoundDataProcessor::ProcessDataRecord(record);
        if (code != kSuccess) return code;

        const std::string data(fXL3HVDecoder.ToJson(record));
        zmq::message_t msg(data.length());
        memcpy((void*) msg.data(), data.c_str(), data.length());
        socket_json->send(msg);
    }
    else if (thisDataId == fXL3VltDataId) {
        ORDataProcessor::EReturnCode code = ORCompoundDataProcessor::ProcessDataRecord(record);
        if (code != kSuccess) return code;

        const std::string data(fXL3VltDecoder.ToJson(record));
        zmq::message_t msg(data.length());
        memcpy((void*) msg.data(), data.c_str(), data.length());
        socket_json->send(msg);
    }
    else if (thisDataId == fFECVltDataId) {
        ORDataProcessor::EReturnCode code = ORCompoundDataProcessor::ProcessDataRecord(record);
        if (code != kSuccess) return code;

        const std::string data(fFECVltDecoder.ToJson(record));
        zmq::message_t msg(data.length());
        memcpy((void*) msg.data(), data.c_str(), data.length());
        socket_json->send(msg);
    }
    else if (thisDataId == fMTCStatusDataId) {
        ORDataProcessor::EReturnCode code = ORCompoundDataProcessor::ProcessDataRecord(record);
        if (code != kSuccess) return code;

        const std::string data(fMTCStatusDecoder.ToJson(record));
        zmq::message_t msg(data.length());
        memcpy((void*) msg.data(), data.c_str(), data.length());
        socket_json->send(msg);
    }
    else if (thisDataId == fEPEDDataId) {
        ORDataProcessor::EReturnCode code = ORCompoundDataProcessor::ProcessDataRecord(record);
        if (code != kSuccess) return code;

        const std::string data(fEPEDDecoder.ToJson(record));
        zmq::message_t msg(data.length());
        memcpy((void*) msg.data(), data.c_str(), data.length());
        socket_json->send(msg);
    }
    else if (thisDataId == fRHDRDataId) {
        ORDataProcessor::EReturnCode code = ORCompoundDataProcessor::ProcessDataRecord(record);
        if (code != kSuccess) return code;

        const std::string data(fRHDRDecoder.ToJson(record));
        zmq::message_t msg(data.length());
        memcpy((void*) msg.data(), data.c_str(), data.length());
        socket_json->send(msg);
    }
    
    return kSuccess;
}

