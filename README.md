# CRCLIB
C library for using multiple 32/64-bit CRC algorithms in a project.
Each algorithm is defined in a descriptor.

The descriptor contains the
* polynome
* initial value
* final xor valut
* whether to input reflect, output reflect, and compute reciprocal

An example table of algorithms is provided with the following algorithms

* CRC32		 0x04C11DB7	     0xFFFFFFFF		0xFFFFFFFF	   ir or
* CRC64-ECMA	 0x42F0E1EBA9EA3693  0x0000000000000000	0x0000000000000000
* CRC64-WE	 0x42F0E1EBA9EA3693  0xFFFFFFFFFFFFFFFF 0xFFFFFFFFFFFFFFFF
* CRC64-XZ	 0x42F0E1EBA9EA3693  0xFFFFFFFFFFFFFFFF	0xFFFFFFFFFFFFFFFF ir or
* CRC64-GO-ISO	 0x000000000000001B  0xFFFFFFFFFFFFFFFF	0xFFFFFFFFFFFFFFFF ir or
* CRC64-GO-ISO-R 0xD800000000000000  0xFFFFFFFFFFFFFFFF	0xFFFFFFFFFFFFFFFF     r

They are tested with the string "123456789"

The expected value comes from
http://www.sunshine2k.de/coding/javascript/crc/crc_js.html

The library is derived from work of Lammert Bies and Bastian Molkenthin.

{Lammert Bies]
https://www.lammertbies.nl/comm/info/crc-calculation
https://www.libcrc.org/
https://github.com/lammertb/libcrc

[Bastian Molkenthin]
http://www.sunshine2k.de/coding/javascript/crc/crc_js.html


Example of use:

	if (init_algorithm(&algo, CRC64_ECMA)) {
		uint64_t crc = calc_crc64 (&algo, "123456789", 9);
	}

The init_algorithm will initiate the "algo" descriptor from a table
of algorithms using CRC64_ECMA as an index to the table.

Whenever you calculate a CRC, you pass a pointer to the algorithm descriptor
into the CRC calculation subroutine together with the input data and length.
