#include "ORXL3HVDecoder.hh"

#include <string>
#include <iomanip>
#include <sstream>

void ORXL3HVDecoder::Swap(UInt_t* dataRecord)
{
    //do not swap the string at the end
    for (size_t idx = 1; idx <  6; idx++) {
        ORUtils::Swap(dataRecord[idx]);
    }
}

const std::string ORXL3HVDecoder::ToJson(UInt_t* record)
{
    std::ostringstream json;
    json << std::setprecision(5);

    json << "{\n"
        << "\"type\": \"xl3_hv\",\n"
        << "\"timestamp\": \"" << TimeStamp(record) << "\",\n"
        << "\"crate_num\": " << CrateNum(record) << ",\n"
        << "\"vlt_a\": " << VoltageA(record) << ",\n"
        << "\"vlt_b\": " << VoltageB(record) << ",\n"
        << "\"crt_a\": " << CurrentA(record) << ",\n"
        << "\"crt_b\": " << CurrentB(record) << "\n"
        << "}";

    return json.str();
}

