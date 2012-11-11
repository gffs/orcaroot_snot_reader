#include "ORSNOTRunDecoder.hh"
#include "ORRunContext.hh"

#include <string>
#include <iomanip>
#include <sstream>
#include <time.h>

const std::string ORSNOTRunDecoder::ToJson(UInt_t* record, UInt_t runNumber, UInt_t subrunNumber)
{
    std::ostringstream json;
    char date_stamp[80];

    json << "{\n"
        << "\"type\": \"run_record\",\n";

    if (IsHeartBeat(record)) {
        json << "\"heartbeat\": true,\n"
            << "\"next_heartbeat\": " << record[2] << ",\n";
    }
    else if (IsRunStart(record)) {
        json << "\"run_start\": true,\n"
            << "\"soft_start\": "
            << ((record[1] & 0x2)? "true": "false") << ",\n"
            << "\"remote_control\": "
            << ((record[1] & 0x4)? "true": "false") << ",\n";
    }
    else if (IsPrepareForSubRun(record)) {
        json << "\"subrun_stop\": true,\n";
    }
    else if (IsSubRunStart(record)) {
        json << "\"subrun_start\": true,\n";
    }
    else if (IsRunStop(record)) {
        json << "\"run_stop\": true,\n"
            << "\"soft_start\": "
            << ((record[1] & 0x2)? "true": "false") << ",\n"
            << "\"remote_control\": "
            << ((record[1] & 0x4)? "true": "false") << ",\n";
    }
    else {
        //some other run record we don't care about
        return json.str();
    }

    time_t time_stamp = (time_t)UtimeOf(record); //that's what we did in ORCA
    strftime(date_stamp, 80, "%Y-%m-%dT%H:%M:%S.00Z", gmtime(&time_stamp));
    json << "\"run_number\": " << runNumber << ",\n"
        << "\"subrun_number\": " << subrunNumber << ",\n"
        << "\"time_stamp\": \"" << date_stamp << "\"\n"
        << "}";

    return json.str();
}

