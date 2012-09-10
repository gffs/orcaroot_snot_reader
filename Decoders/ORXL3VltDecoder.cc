#include "ORXL3VltDecoder.hh"

#include <string>
#include <iomanip>
#include <sstream>

void ORXL3VltDecoder::Swap(UInt_t* dataRecord)
{
    //do not swap the string at the end
    for (size_t idx = 1; idx <  10; idx++) {
        ORUtils::Swap(dataRecord[idx]);
    }
}

const std::string ORXL3VltDecoder::ToJson(UInt_t* record)
{
    std::ostringstream json("{\n");
    json << std::setprecision(4);

    json << "\"type\": \"xl3_vlt\",\n"
        << "\"timestamp\": \"" << TimeStamp(record) << "\",\n"
        << "\"crate_num\": " << CrateNum(record) << ",\n"
        << "\"VCC\": " << VoltageForIndex(0, record) << ",\n"
        << "\"VEE\": " << VoltageForIndex(1, record) << ",\n"
        //<< "\"VP8\": " << VoltageForIndex(2, record) << ",\n"
        << "\"VP24\": " << VoltageForIndex(3, record) << ",\n"
        << "\"VM24\": " << VoltageForIndex(4, record) << ",\n"
        << "\"TMP0\": " << VoltageForIndex(5, record) << ",\n"
        << "\"TMP1\": " << VoltageForIndex(6, record) << ",\n"
        << "\"TMP2\": " << VoltageForIndex(7, record) << ",\n"
        << "}";

    return json.str();
}

