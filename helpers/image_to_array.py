import sys, os
from xml.dom import minidom
from PIL import Image

im = Image.open('obama.bmp')
rgb_im = im.convert('RGB')

output_file = 'out.h'

bigassstring = ""

#Write .h-file
with open(output_file, 'w') as file:
    #Data Structure
    bigassstring += "#include <stdint.h>\n"
    bigassstring += "uint8_t bm[25][45][3] = {\n"

    for i in range(25):
        bigassstring += "{\n"
        for j in range(45):
            r, g, b = rgb_im.getpixel((j, i))
            r //= 10
            g //= 10
            b //= 10
            if j == 44:
                bigassstring += "{" + str(r) + "," + str(g) + "," + str(b) + "}\n"
            else:
                bigassstring += "{" + str(r) + "," + str(g) + "," + str(b) + "},\n"

        if i == 24:
            bigassstring += "}\n"
        else:
            bigassstring += "},\n"

    #Data Structure 2 and Definition Boilerplate
    bigassstring += "};\n\n"

    file.write(bigassstring)

