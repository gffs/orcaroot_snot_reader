#include "ORFIFODecoder.hh"

#include <string>
#include <iomanip>
#include <sstream>

const std::string ORFIFODecoder::ToJson(UInt_t* record)
{
    std::ostringstream json;
    json << std::setprecision(3);

    json << "{\n"
        << "\"type\": \"fifo_state\",\n"
        << "\"crate_num\": " << CrateNum(record) << ",\n"
        << "\"fifo\": [ ";

    for (unsigned char i = 0; i < 16; i++) {
        if (i) json << ", ";
        json << FIFOForSlot(i, record);
    }
    json << "],\n"
        << "\"XL3_buffer\": " << XL3Buffer(record) << "\n"
        << "}";

    return json.str();
}

