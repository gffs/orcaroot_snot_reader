#include "OREPEDDecoder.hh"

#include <string>
#include <iomanip>
#include <sstream>

const std::string OREPEDDecoder::ToJson(UInt_t* record)
{
    std::ostringstream json;

    json << "{\n"
        << "\"type\": \"eped_record\",\n"
        << "\"coarse_delay\": " << CoarseDelay(record) << ",\n"
        << "\"fine_delay\": " << FineDelay(record) << ",\n"
        << "\"charge_pulse_amp\": " << ChargePulseAmp(record) << ",\n"
        << "\"pedestal_width\": " << PedestalWidth(record) << ",\n"
        << "\"cal_type\": " << CalType(record) << ",\n"
        << "\"step_number\": " << StepNumber(record) << "\n"
        << "}";

    return json.str();
}

