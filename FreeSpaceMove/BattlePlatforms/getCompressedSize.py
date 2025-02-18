import os
size = 0
for index in range(int("0x73",16)):
    if index < 16:
        leadingZero = "0"
    else:
        leadingZero = ""

    size += os.path.getsize(("dmp/BPImage"+leadingZero+('{0:x}'.format(index)).upper())+".lz77")
    size += os.path.getsize(("dmp/BPImage"+leadingZero+('{0:x}'.format(index)).upper())+".pal")

print(hex(size))