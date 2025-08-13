import re
import os

from PIL import Image, ImageFont, ImageDraw

def get_max_height(font: ImageFont.FreeTypeFont, char_list: list[str], font_size: int) -> int:
    max_height = 0

    for char in chars:
        width, height = font.getmask(char).size
        if height > max_height:
            max_height = height

    return max_height

def generate_font(char_list : list[str], size : int, font_name : str) -> None:
    current_dir = os.path.curdir

    with open(current_dir + "/output/" + font_name + ".c", "w") as output:
        output.write(f"#include \"fonts.h\"\n")
        output.write(f"const uint8_t {font_name}_Table[] = \n{{\n\t")

        font = ImageFont.truetype(current_dir + "/fonts/" +"arial.ttf", size)
        height = get_max_height(font, char_list, size)

        print("============Max height: {0}".format(height))

        for char in chars:
            width, __unused = font.getmask(char).size
            width = width + 4

            img = Image.new('1', (width, height) , 0)
            draw = ImageDraw.Draw(img)
            draw.text((-1,0), char, font=font, fill=1)
            pixels = list(img.getdata())

            bitmap = []

            for y in range(img.height):
                byte = 0
                for x in range(img.width):
                    if pixels[y * img.width + x]:
                        byte |= (1 << (7 - (x % 8)))
                    if x % 8 == 7:
                        bitmap.append(byte)
                        byte = 0

            bytes_per_line = int(width / 8)# + int(width % 8 != 0)

            print(f"// '{char}' ({width}x{height}) pixels")
            output.write(f"// '{char}' {width} pixels wide\n\t")

            byte_count = 0
            for b in bitmap:
                #print(f"0x{b:02X},", end="")
                print(f"0x{b:08b}"[2:], end="")
                output.write(f"0x{b:02X},")
                byte_count += 1

                if(byte_count == bytes_per_line):
                    byte_count = 0
                    print("\n", end="")
                    output.write("\n\t")
        
        output.write("\n};\n")
        output.write(f"sFONT {font_name} = {{\n")
        output.write(f"\t{font_name}_Table,\n")
        output.write(f"\t{width},\n")
        output.write(f"\t{size - 1},\n")
        output.write("};")

chars = [' ', '!', '"', '#', '$', '%', '&', "'", '(', ')', '*', '+', ',', '-', '.', '/', '0']
         #'1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A',
         #'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
         #'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c',
         #'d', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
         #'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~']

generate_font(chars, 48, "Arial80")