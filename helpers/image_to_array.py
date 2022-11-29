from PIL import Image

im = Image.open('connected.bmp')
rgb_im = im.convert('RGB')

output_file = '../firmware-esp32dev/src/connected.h'

bigassstring = ""

#Write .h-file
with open(output_file, 'w') as file:
    #Data Structure
    bigassstring += "#include <stdint.h>\n"
    bigassstring += "uint8_t connected_bm[25][45][3] = {\n"

    for i in range(25):
        bigassstring += "{\n"
        for j in range(45):
            r, g, b = rgb_im.getpixel((j, i))
            r //= 5
            g //= 5
            b //= 5
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

