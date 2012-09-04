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
    "timestamp": "yyyy-MM-ddTHH:mm:ss.SSSZ" //ORCA
    "crate_num": 0, //ORCA
    "slot_mask": 0xffff0000,
    "channel_mask": [ 0xffffffff, ..., 0xffffffff ], //all 16 slots
    "error_flags": 0x0000,
    "counts": [ [ 0*0, ..., 0*31], ..., [ 7*0, ..., 7*31 ], //8 slots * 32 channels
    }

FIFO state
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
    "timestamp": "yyyy-MM-ddTHH:mm:ss.SSSZ" //ORCA
    "crate_num": 0, //ORCA
    "slot_mask": 0xffff0000,
    "channel_mask": [ 0xffffffff, ..., 0xffffffff ], //all 16 slots
    "error_flags": 0x0000,
    "adc": [ [ 0*0, ..., 0*31], ..., [ 7*0, ..., 7*31 ], //16 slots * 32 channels
    }

