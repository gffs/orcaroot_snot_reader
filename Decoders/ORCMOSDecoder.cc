#include "ORCMOSDecoder.hh"

#include <string>
#include <sstream>

void ORCMOSDecoder::Swap(UInt_t* dataRecord)
{
    //do not swap the string at the end
    for (size_t idx = 1; idx < 21+8*32; idx++) {
        ORUtils::Swap(dataRecord[idx]);
    }
}

const std::string ORCMOSDecoder::ToJson(UInt_t* record)
{
    std::ostringstream json("{\n");

    json << "\"type\":\"cmos_counts\",\n"
        << "\"timestamp\": \"" << TimeStamp(record) << "\",\n"
        << "\"crate_num\": " << CrateNum(record) << ",\n"
        << "\"slot_mask\": " << SlotMask(record) << ",\n"
        << "\"channel_mask\": [ ";

    for (unsigned char i = 0; i < 16; i++) {
        if (i) json << ", ";
        json << ChannelMaskForSlot(i, record);
    }
    json << "],\n"
        << "\"error_flags\": " << ErrorFlags(record) << ",\n"
        << "\"counts\": [ ";

    for (unsigned char slot = 0; slot < 8; slot++) {
        if (slot) json << ",\n";
        json << "[ ";
        for (unsigned char channel = 0; channel < 32; channel++) {
            if (channel) json << ", ";
            json << CMOSCounterForSlotAndChannel(slot, channel, record);
        }
        json << " ]";
    }
    json << "]\n";
    json << "}";
    return json.str();
}

