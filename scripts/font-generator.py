import os

from PIL import Image, ImageFont, ImageDraw

class ConfigurationConstants:
    BYTES_PER_LINE = 16

class CharProperties:
    def __init__(self, char : str, width : int, height : int, i_start : int, i_end : int):
        self.char = char
        self.width = width
        self.height = height
        self.index_start = i_start
        self.index_end = i_end

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

        index_start = 0
        index_end = 0

        char_properties : list[CharProperties] = []

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

            width_bytes = int(width / 8) + ((width % 8) != 0)
            
            counter = 0
            bit_counter = 7
            bytes = []
            byte = 0

            for px in pixels:
                if px:
                    byte |= 1 << bit_counter
                bit_counter -= 1
                counter += 1

                if bit_counter == -1:
                    bytes.append(byte)
                    index_end += 1
                    bit_counter = 7
                    byte = 0

                if counter == width:
                    bytes.append(byte)
                    index_end += 1
                    bit_counter = 7
                    byte = 0
                    counter = 0

            index_end -= 1
            

            output.write(f"\n\t// '{char}' ({width}x{height}) pixels, start[{index_start}] end[{index_end}]\n\t")
            char_properties.append(CharProperties(char, width, height, index_start, index_end))

            byte_count = 0
            for b in bytes:
                output.write(f"0x{b:02X},")
                byte_count += 1

                if(byte_count == ConfigurationConstants.BYTES_PER_LINE):
                    byte_count = 0
                    output.write("\n\t")
            
            index_end += 1
        

        output.write("\n};\n")
        output.write(f"const uint32_t {font_name}_LUT[] = \n{{\n")
        for char_p in char_properties:
            output.write(f"\t{char_p.width}, {char_p.index_start}, {char_p.index_end}, //'{char_p.char}'\n")
        output.write("};\n")

        output.write(f"sFONT {font_name} = {{\n")
        output.write(f"\t{font_name}_Table,\n")
        output.write(f"\t{width},\n")
        output.write(f"\t{size - 1},\n")
        output.write("};")

chars = [' ', '!', '"', '#', '$', '%', '&', "'", '(', ')', '*', '+', ',', '-', '.', '/', '0',
        '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A',
        'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c',
        'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~']

generate_font(chars, 48, "Arial80")