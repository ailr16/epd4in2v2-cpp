import re
import os

from PIL import Image, ImageFont, ImageDraw

def compute_max_width(char_list : list[str]) -> float:
    max_width = 0

    for char in char_list:
        font = ImageFont.truetype("arial.ttf", 48)

        bbox = font.getbbox(char)
        width = bbox[2] - bbox[0]
        if(width > max_width):
            max_width = width

    return max_width


def generate_font(char_list : list[str], size : int, font_name : str) -> None:

    with open("/home/ailr16/Documents/font.c", "w") as output:

        output.write(f"#include \"fonts.h\"\n")
        output.write(f"const uint8_t {font_name}_Table[] = \n{{\n\t")

        font = ImageFont.truetype("arial.ttf", size)

        width = compute_max_width(char_list)

        for char in chars:
            img = Image.new('1', (width, size - 1) , 0)
            draw = ImageDraw.Draw(img)
            draw.text((0,-8), char, font=font, fill=1)
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

            bytes_per_line = int(width / 8)

            print(f"// '{char}' ({width} pixels wide)")
            output.write(f"// '{char}' {width} pixels wide\n\t")

            byte_count = 0
            for b in bitmap:
                print(f"0x{b:02X},", end="")
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

chars = []

with open("/home/ailr16/Documents/git/e-Paper/RaspberryPi_JetsonNano/c/lib/Fonts/font8.c") as f:
    current_line = f.readline()
    while current_line.find('const') == -1:
        current_line = f.readline()

    while True:
        current_line = f.readline()

        if not current_line:
            break

        if "@" in current_line:
            char_in_current_line = current_line[re.search("'(.)'",current_line).start() + 1]
            chars.append(char_in_current_line)


generate_font(chars, 48, "Arial24")