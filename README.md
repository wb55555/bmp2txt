bmp2txt
=====

### Function
- Read 1, 4, 8 or 24bit's .bmpfile.
- Show datas of bmpfliehead and bmpfliehead on the terminal.
- Output all of the .bmpflie's datas in a .txtfile.

### Dependencies
- C++ language
- Linux
- vim editor

### Running
```
make
./b2t bmpname.bmp txtname.txt
vim txtname.txt
:set tabstop=16
```

### File Description
- README.md-----//help
- bmp2txt.cpp---//program
- bmp.h---------//definition of bmpfile's fliehead, fliehead and colortable
- 1bit.bmp------//example of bmpfile
- 4bit.bmp------//example of bmpfile
- 8bit.bmp------//example of bmpfile
- 24bit.bmp-----//example of bmpfile
- Makefile------//auto-compile out a b2t file