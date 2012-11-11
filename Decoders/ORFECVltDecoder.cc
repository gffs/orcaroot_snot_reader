#include "ORFECVltDecoder.hh"

#include <string>
#include <iomanip>
#include <sstream>

void ORFECVltDecoder::Swap(UInt_t* dataRecord)
{
    //do not swap the string at the end
    for (size_t idx = 1; idx <  24; idx++) {
        ORUtils::Swap(dataRecord[idx]);
    }
}

const std::string ORFECVltDecoder::ToJson(UInt_t* record)
{
    std::ostringstream json;
    json << std::setprecision(4);

    json << "{\n"
        << "\"type\": \"fec_vlt\",\n"
        << "\"timestamp\": \"" << TimeStamp(record) << "\",\n"
        << "\"crate_num\": " << CrateNum(record) << ",\n"
        << "\"slot_num\": " << SlotNum(record) << ",\n"

        << "\"voltage\": [ ";

    for (unsigned char i = 0; i < 21; i++) {
        if (i) json << ", ";
        json << VoltageForIndex(i, record);
    }

    json << " ]\n";
    json << "}";

    return json.str();
}

