import os
file = open("VanillaBattlePlatforms.event", "w")
for index in range(int("0x73",16)):
    
    if index < 16:
        leadingZero = "0"
    else:
        leadingZero = ""
    
    hexIndex = ('{0:x}'.format(index)).upper()

    file.write("BPEntry(0x" + leadingZero + hexIndex + ",BPImage"+ leadingZero + hexIndex + ",BPPalette" + leadingZero + hexIndex + ")\n")

    file.write("ALIGN 4; BPImage"+ leadingZero + hexIndex + ":\n")
    file.write("#incbin \"dmp/BPImage" + leadingZero + hexIndex + ".lz77\"\n")

    file.write("ALIGN 4; BPPalette"+ leadingZero + hexIndex + ":\n")
    string = "BYTE "
    palette = open("dmp/BPImage" + leadingZero + hexIndex + ".pal","rb")
    for counter in range(int("0x20",16)):
        string = (string+"$"+('{0:x}'.format(ord(palette.read(1))).upper()+" "))
    palette.close()
    file.write(string+"\n")
    
    file.write("\n")
file.close()