sno+ orcaroot
=============
*translator from ORCA binary data-file/stream to JSON for selected packets*

Dependencies
------------
    orcaroot: svn://orca.physics.unc.edu/OrcaRoot
    root: https://root.cern.ch/svn/root/trunk
    zeromq: git://github.com/zeromq/libzmq.git (brew -v install --devel --debug zmq)
    cppzmq: git://github.com/zeromq/cppzmq.git (for ZMQ v. > 3.0)

Installation
------------
    $ make clean
    $ make

Usage
-----
    $ ./orcaroot_snot_reader Run14*
    $ ./orcaroot_snot_reader 127.0.0.1:44666
    $ ./orcaroot_daemon.sh

The JSON stream is sent to a ZMQ PUB socket bound to `tcp://localhost:5028` and includes

CMOS counts
-----------
CMOS counts as shipped by XL3 with a timestamp added when the packet reaches ORCA,
maximum 8 slots per packet, the slot order matches `slot_mask` starting from the LSB,
there are always 32 channels per slot present, but only the `channel_mask` ones are relevant.

    {
    "type": "cmos_counts",
    "timestamp": "yyyy-MM-ddTHH:mm:ss.SSZ" //ORCA
    "crate_num": 0, //ORCA
    "slot_mask": 0xffff,
    "channel_mask": [ 0xffffffff, ..., 0xffffffff ], //all 16 slots
    "error_flags": 0x0000,
    "counts": [ [ 0*0, ..., 0*31], ..., [ 7*0, ..., 7*31 ] //8 slots * 32 channels
    }

FEC FIFO state
----------
The states of FEC FIFOs and XL3 memory buffer are pushed by XL3 as a body of the PING packet. ORCA adds the crate number.

    {
    "type": "fifo_state",
    "crate_num": 0,
    "fifo": [ 0.0, ... ], //16 slots
    "XL3_buffer": 0.0,
    }

PMT base currents
-----------------
PMT base currents as recieved from XL3. ORCA adds a timestamp, and the crate number. All the 16*32 ADC values are filled, only the masked in are useful.

    {
    "type": "pmt_base_current",
    "timestamp": "yyyy-MM-ddTHH:mm:ss.SSZ" //ORCA
    "crate_num": 0, //ORCA
    "slot_mask": 0xffff,
    "channel_mask": [ 0xffffffff, ..., 0xffffffff ], //all 16 slots
    "error_flags": 0x0000,
    "adc": [ [ 0*0, ..., 0*31], ..., [ 7*0, ..., 7*31 ], //16 slots * 32 channels
    "busy_flag": [ [ 0*0, ..., 0*31], ..., [ 7*0, ..., 7*31 ] //16 slots * 32 channels
    }

HV status
---------
Voltages and currents as shipped by XL3, the scale is stretched.

    {
    "type": "xl3_hv",
    "timestamp": "yyyy-MM-ddTHH:mm:ss.SSZ" //ORCA
    "crate_num": 0, //ORCA
    "vlt_a": 0., //V
    "vlt_b": 0., //V
    "crt_a": 0., //mA
    "crt_b": 0. //mA
    }

XL3 voltages
------------

    {
    "type": "xl3_vlt",
    "timestamp": "yyyy-MM-ddTHH:mm:ss.SSZ" //ORCA
    "crate_num": 0, //ORCA
    "VCC": 0.,
    "VEE": 0.,
    "VP24": 0.,
    "VM24": 0.,
    "TMP0": 0.,
    "TMP1": 0.,
    "TMP2": 0.
    }

FEC voltages
------------
FEC voltages a packet per slot. There are 21 voltages in the array: -24V Sup, -15V Sup, VEE, -3.3V Sup, -2.0V Sup, 3.3V Sup, 4.0V Sup, VCC, 6.5V Sup, 8.0V Sup, 15V Sup, 24V Sup, -2.0V Ref, -1.0V Ref, 0.8V Ref, 1.0V Ref, 4.0V Ref, 5.0V Ref, Temp in deg C, Cal DAC, HV current in mA. 

    {
    "type": "fec_vlt",
    "timestamp": "yyyy-MM-ddTHH:mm:ss.SSZ" //ORCA
    "crate_num": 0, //ORCA
    "slot_num": 0, //ORCA
    "voltage": [ 0., ... ] // 21 float voltages
    }

Run record
---------------
a variable content packet including heartbeats, run start/stop, subrun start/stop.

    {
    "type": "run_record",
    //either
    "heartbeat": true,
    "next_heartbeat": 30, //sec
    //or
    "run_start": true,
    "soft_start": false, //GTIDs reset to zero
    "remote_control": false, 
    //or
    "subrun_stop": true,
    //or
    "subrun_start": true,
    //or
    "run_stop": true,
    "soft_start": true, //next run will start without GTID reset
    "remote_control": false,
    //all the run records
    "run_number": 0,
    "subrun_number": 0,
    "time_stamp": "yyyy-MM-DDTHH:mm:ss.SSZ"
    }

MTC Status record
-----------------
MTC status pulled from MTCD each second.

    {
    "type": "mtc_status",
    "GTID": 0x123456,
    "cnt_10MHz": 0x1234567890123, //53 bits, 10 MHz ticks since 1996-01-01T00:00:00Z
    "time_10MHz": "yyyy-MM-DDTHH:mm:ss.SSZ", //from cnt_10MHz
    "data_available": false,
    "read_pointer": 0,
    "write_next_pointer": 0,
    "num_records_in_mem": 0, //from read and write pointers and data available bit
    }

EPED record
-----------
ECA info at the beginning of every ECA step

    {
    "type": "eped_record",
    "coarse_delay": 100, //nsec
    "fine_delay": 0, //clicks
    "charge_pulse_amp": 0, //clicks
    "pedestal_width": 60, //nsec
    "cal_type": 11, //pattern ID (1 to 4) + 10 * (1 ped, 2 tslope, 3 qslope)
    "step_number": 0
    }

RHDR record
-----------
Run type information duplicating the run document

    {
    "type": "rhdr_record",
    "date": day + month * 100 + year * 10000,
    "time": sec * 100 + min * 10000 + year * 1000000,
    "daq_code_version": 8045, // svn rev
    "run_number": 0,
    "calibration_trial_number": 0,
    "source_mask": 0,
    "run_mask": 0, // 64bit
    "gt_crate_mask": 0
    }

