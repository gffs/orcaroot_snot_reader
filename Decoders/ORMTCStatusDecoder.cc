#include "ORMTCStatusDecoder.hh"

#include <string>
#include <iomanip>
#include <sstream>
#include <time.h>
#include <stdio.h>

const std::string ORMTCStatusDecoder::Time10MHz(UInt_t* record)
{
    std::string time_stamp;

    unsigned long long ticks = record[3] + ((record[4] & 0x1fffffULL) << 32);
    time_t t_stamp = (time_t)(ticks * 100.e-9);
    ticks = (unsigned long long)(ticks * 100.e-7 - t_stamp * 100 + 0.5);
    t_stamp += 820454400; //1996-01-01T00:00:00Z

    char date_stamp[80];
    strftime(date_stamp, 80, "%Y-%m-%dT%H:%M:%S.", gmtime(&t_stamp));
    time_stamp = date_stamp;

    t_stamp = (time_t)ticks;
    sprintf(date_stamp, "%02ldZ", t_stamp);
    time_stamp += date_stamp;

    return time_stamp;
}

UInt_t ORMTCStatusDecoder::NumRecordsInMem(UInt_t* record)
{
    int num_records = 0;

    num_records = WriteNextPointer(record) - ReadPointer(record);
    if (num_records < 0 || (num_records == 0 && DataAvailable(record))) {
        num_records += 0x100000;
    }

    return (UInt_t)num_records;
}

const std::string ORMTCStatusDecoder::ToJson(UInt_t* record)
{
    std::ostringstream json;

    json << "{\n"
        << "\"type\": \"mtc_status\",\n"
        << "\"GTID\": " << GTID(record) << ",\n"
        << "\"cnt_10MHz\": " << Cnt10MHz(record) << ",\n"
        << "\"time_10MHz\": \"" << Time10MHz(record) << "\",\n"
        << "\"data_available\": " << (DataAvailable(record)? "true": "false") << ",\n"
        << "\"read_pointer\": " << ReadPointer(record) << ",\n"
        << "\"write_next_pointer\": " << WriteNextPointer(record) << ",\n"
        << "\"num_records_in_mem\": " << NumRecordsInMem(record) << "\n"
        << "}";

    return json.str();
}

