# Boot Loader micro Executable (BLUE)

A minimalistic bootloader for the nRF52840

Features:
- TODO

Missing:
- TODO

## User Guide

TODO

## HEX file format

See https://en.wikipedia.org/wiki/Intel_HEX

```
:10000000000004209D080000BB0200001502000053
:                                           start code
 10                                         length of the data field
   0000                                     address, relative to a base address [big endian]
       00                                   record type 00==data
                                                        01==end of file
                                                        02==extended segment address (up to 1MB image)
                                                        03==start segment address
                                                        04==extended linear address (32-bit addressing)
         000004209D080000BB02000015020000   data
                                         53 checksum for the record (so LSB of sum of all bytes is 00)
```

See [blue_annotated.md](blue_annotated.md) for an example.