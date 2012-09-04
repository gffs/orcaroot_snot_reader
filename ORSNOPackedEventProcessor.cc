// ORSNOPackedEventProcessor.cc

#include "ORSNOPackedEventProcessor.hh"
#include "ORRunContext.hh"
#include "ORLogger.hh"
#include <iostream>

using namespace std;

ORSNOPackedEventProcessor::ORSNOPackedEventProcessor(std::string /*label*/)
{
    SetComponentBreakReturnsFailure();

    fMTCProcessor = new ORDataProcessor(&fMTCDecoder);
    AddProcessor(fMTCProcessor);

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

    context = new zmq::context_t(1);
    socket_json = new zmq::socket_t(*context, ZMQ_PUB);
    socket_json->bind("tcp://localhost:5028");
}


ORSNOPackedEventProcessor::~ORSNOPackedEventProcessor()
{
    delete socket_json;
    delete context;

    delete fMTCProcessor;
    delete fPMTProcessor;
    delete fCMOSProcessor;
    delete fCaenProcessor;
    delete fRunProcessor;
    delete fFIFOProcessor;
    delete fPMTBaseCurrentProcessor;
}


ORDataProcessor::EReturnCode ORSNOPackedEventProcessor::StartRun()
{

    fMTCDataId = fMTCProcessor->GetDataId();
    fPMTDataId = fPMTProcessor->GetDataId();
    fCMOSDataId = fCMOSProcessor->GetDataId();
    fCaenDataId = fCaenProcessor->GetDataId();
    fRunId = fRunProcessor->GetDataId();
    fFIFODataId = fFIFOProcessor->GetDataId();
    fPMTBaseCurrentDataId = fPMTBaseCurrentProcessor->GetDataId();

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

        /*
        cout << "Run Packet obtained" << endl;
        if (record[1] & 0x8) cout << "Run HeartBeat obtained" << endl;
        else if (record[1] & 0x1) {
            cout << "Run Start obtained" << endl;
            if (record[1] & 0x2) cout << "was soft start" << endl;
            if (record[1] & 0x4) cout << "was remote control start" << endl;
        }
        else {
            cout << "Run End obtained" << endl;
            if (record[1] & 0x2) cout << "soft end" << endl;
            if (record[1] & 0x4) cout << "remote control" << endl;
        }
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
    
    return kSuccess;
}

