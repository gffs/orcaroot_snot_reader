#include "ORPMTBaseCurrentDecoder.hh"

#include <string>
#include <sstream>

void ORPMTBaseCurrentDecoder::Swap(UInt_t* dataRecord)
{
    //do not swap the timestamp string at the end
    for (size_t idx = 1; idx < 20+16*8+16*8; idx++) {
        ORUtils::Swap(dataRecord[idx]);
    }
}

const std::string ORPMTBaseCurrentDecoder::ToJson(UInt_t* record)
{
    std::ostringstream json("{\n");

    json << "\"type\": \"pmt_base_current\",\n"
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
        << "\"adc\": [ ";

    for (unsigned char slot = 0; slot < 16; slot++) {
        if (slot) json << ",\n";
        json << "[ ";
        for (unsigned char channel = 0; channel < 32; channel++) {
            if (channel) json << ", ";
            json << (unsigned short)ADCForSlotAndChannel(slot, channel, record);
        }
        json << " ]";
    }
    json << "],\n"
        << "\"busy\": [ ";

    for (unsigned char slot = 0; slot < 16; slot++) {
        if (slot) json << ",\n";
        json << "[ ";
        for (unsigned char channel = 0; channel < 32; channel++) {
            if (channel) json << ", ";
            json << (unsigned short)BusyForSlotAndChannel(slot, channel, record);
        }
        json << " ]";
    }

    json << "]";

    json << "}";
    return json.str();
}

