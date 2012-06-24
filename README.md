HexDump
=======

Creates a text file containing the hex dump of a binary file (also does the opposite).

```
HexDump.exe [-r] filein fileout

        Takes a binary file and produces a hexdump

-r      Takes a hexdump and produces a binary file
```

### Samples

```
hexdump test.jpg test.txt
```

Reads test.jpg and produces test.txt which contains a formated hexdump like the following:

```
FF D8 FF E0 00 10 4A 46 49 46 00 01 01 01 00 96 00 96 00 00 ; ......JFIF..........
FF DB 00 43 00 03 02 02 03 02 02 03 03 03 03 04 03 03 04 05 ; ...C................
08 05 05 04 04 05 0A 07 07 06 08 0C 0A 0C 0C 0B 0A 0B 0B 0D ; ....................
0E 12 10 0D 0E 11 0E 0B 0B 10 16 10 11 13 14 15 15 15 0C 0F ; ....................
17 18 16 14 18 12 14 15 14 FF DB 00 43 01 03 04 04 05 04 05 ; ............C.......
09 05 05 09 14 0D 0B 0D 14 14 14 14 14 14 14 14 14 14 14 14 ; ....................
...
```

```
hexdump -r test.txt test2.jpg
```

Reads test.txt expecting a format like that above and produces the binary file test2.jpg

- hex values can be in either upper or lower case. 
- hex values can be seperated by spaces, tabs, linefeeds or carriage returns
- ; is a comment delimiter and everything to the next carriage return is ignored.