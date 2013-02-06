#include "ORRHDRDecoder.hh"

#include <string>
#include <iomanip>
#include <sstream>

const std::string ORRHDRDecoder::ToJson(UInt_t* record)
{
    std::ostringstream json;

    json << "{\n"
        << "\"type\": \"rhdr_record\",\n"
        << "\"date\": " << Date(record) << ",\n"
        << "\"time\": " << Time(record) << ",\n"
        << "\"daq_code_version\": " << DaqCodeVersion(record) << ",\n"
        << "\"run_number\": " << RunNumber(record) << ",\n"
        << "\"calibration_trial_number\": " << CalibrationTrialNumber(record) << ",\n"
        << "\"source_mask\": " << SourceMask(record) << ",\n"
        << "\"run_mask\": " << RunMask(record) << ",\n"
        << "\"gt_crate_mask\": " << GtCrateMask(record) << "\n"
        << "}";

    return json.str();
}

