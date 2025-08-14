import os

from PIL import Image, ImageFont, ImageDraw

def get_max_height(font: ImageFont.FreeTypeFont, char_list: list[str], font_size: int) -> int:
    max_height = 0

    for char in chars:
        left, top, right, bottom = font.getbbox(char)
        height = bottom

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
        ascent, descent = font.getmetrics()
        baseline_offset = ascent 

        print("============Max height: {0}".format(height))

        index_start = 0
        index_end = 0

        for char in chars:
            index_start = index_end

            bbox = font.getbbox(char)
            width = bbox[2] - bbox[0]

            img = Image.new('1', (width, height) , 0)
            draw = ImageDraw.Draw(img)

            x_offset = -bbox[0]
            y_offset = -bbox[1]

            draw.text((x_offset, 0), char, font=font, fill=1)
            pixels = list(img.getdata())

            bitmap = []

            counter = 0
            for i in pixels:
                print(i, end="")
                counter += 1
            
                if counter == img.width:
                    counter = 0
                    print("\n", end="")
            print("\n", end="")

            width_bytes = int(img.width / 8) + ((img.width % 8) != 0)
            print(f"width: {img.width}")
            print(f"needed bytes for width: {width_bytes}")

            #for y in range(img.height):
            #    byte : bytearray = 0
            #    for x in range(img.width):
            #        if pixels[y * img.width + x]:
            #            byte |= (1 << (7 - (x % 8)))
            #        if x % 8 == 7:
            #            bitmap.append(byte)
            #            byte = 0
            #        index_end += 1



            #bytes_per_line = int(width / 8) + int(width % 8 != 0)

            #print(f"// '{char}' ({width}x{height}) pixels")
            #print(f"// '{char}' start[{index_start}] end[{index_end}]")
            #output.write(f"// '{char}' {width} pixels wide\n\t")


            #byte_count = 0
            #for b in bitmap:
            #    #print(f"0x{b:02X},", end="")
            #    print(f"0x{b:08b}"[2:], end="")
            #    output.write(f"0x{b:02X},")
            #    byte_count += 1

            #    if(byte_count == bytes_per_line):
            #        byte_count = 0
            #        print("\n", end="")
            #        output.write("\n\t")
            
            index_end += 1
        
        output.write("\n};\n")
        output.write(f"sFONT {font_name} = {{\n")
        output.write(f"\t{font_name}_Table,\n")
        output.write(f"\t{width},\n")
        output.write(f"\t{size - 1},\n")
        output.write("};")

def abc():
    chars = [' ', '!', '"', '#', '$', '%', '&', "'", '(', ')', '*', '+', ',', '-', '.', '/', '0',
            '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A',
            'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
            'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c',
            'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
            'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~']
    
chars = ["A", "b", "j"]

generate_font(chars, 48, "Arial80")