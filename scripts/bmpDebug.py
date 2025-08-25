import argparse
import sys

class Utils:
    def read_bytes(data:list[bytes], nbytes:int, start:int) -> int:
        result = 0

        bits = (nbytes - 1) * 8
        for i in range(0, nbytes):
            result |= int(data[start + nbytes - 1 - i]) << bits - (8 * i)
            
        return result

    def write_bytes(value: int, nbytes: int) -> bytes:
        return value.to_bytes(nbytes, byteorder="little")
    
    def validate_data_length(data:list, range:tuple) -> bool:
        if len(data) == range[1] - range[0]:
            return True
        
        return False

class PrintMode:
    HEX = 0
    INT = 1

class Header:
    MEMORY_RANGE = (0, 14)

    def __init__(self, header_data:bytes) -> None:
        if not Utils.validate_data_length(header_data, self.MEMORY_RANGE):
            print("Header must be {0} bytes!".format(self.MEMORY_RANGE[1]))
            print("Finishing read with an error.")
            return
        
        self.signature = Utils.read_bytes(header_data, 2, 0)
        self.file_size = Utils.read_bytes(header_data, 4, 2)
        self.reserved = Utils.read_bytes(header_data, 4, 6)
        self.data_offset = Utils.read_bytes(header_data, 4, 10)
    
    def to_bytes(self) -> bytes:
        return(
            Utils.write_bytes(self.signature, 2) +
            Utils.write_bytes(self.file_size, 4) +
            Utils.write_bytes(self.reserved, 4) +
            Utils.write_bytes(self.data_offset, 4)
        )

    def print(self, mode:int) -> None:
        if mode == PrintMode.HEX:
            print(f"Signature: {self.signature:02X}")
            print(f"File Size: {self.file_size:02X}")
            print(f"Reserved: {self.reserved:02X}")
            print(f"Data Offset:{self.data_offset:02X}")

        if mode == PrintMode.INT:
            print(f"Signature: {self.signature}")
            print(f"File Size: {self.file_size}")
            print(f"Reserved: {self.reserved}")
            print(f"Data Offset: {self.data_offset}")

class InfoHeader:
    MEMORY_RANGE = (14, 54)

    def __init__(self, data:bytes) -> int:
        if not Utils.validate_data_length(data, self.MEMORY_RANGE):
            print("Header must be {0} bytes!".format(self.MEMORY_RANGE[1]))
            print("Finishing read with an error.")
            return
        
        self.size = Utils.read_bytes(data, 4, 0)
        self.width = Utils.read_bytes(data, 4, 4)
        self.height = Utils.read_bytes(data, 4, 8)
        self.planes = Utils.read_bytes(data, 2, 12)
        self.bit_per_px = Utils.read_bytes(data, 2, 14)
        self.compression = Utils.read_bytes(data, 4, 16)
        self.image_size = Utils.read_bytes(data, 4, 20)
        self.x_px_per_m = Utils.read_bytes(data, 4, 24)
        self.y_px_per_m = Utils.read_bytes(data, 4, 28)
        self.colors = Utils.read_bytes(data, 4, 32)
        self.important_color = Utils.read_bytes(data, 4, 36)

    def to_bytes(self) -> bytes:
        return(
            Utils.write_bytes(self.size, 4) +
            Utils.write_bytes(self.width, 4) +
            Utils.write_bytes(self.height, 4) +
            Utils.write_bytes(self.planes, 2) +
            Utils.write_bytes(self.bit_per_px, 2) +
            Utils.write_bytes(self.compression, 4) +
            Utils.write_bytes(self.image_size, 4) +
            Utils.write_bytes(self.x_px_per_m, 4) +
            Utils.write_bytes(self.y_px_per_m, 4) +
            Utils.write_bytes(self.colors, 4) +
            Utils.write_bytes(self.important_color, 4)
        )

    def print(self, mode:int) -> None:
        if mode == PrintMode.HEX:
            print(f"Size: {self.size:02X}")
            print(f"Width: {self.width:02X}")
            print(f"Height: {self.height:02X}")
            print(f"Planes: {self.planes:02X}")
            print(f"Bits per pixel: {self.bit_per_px:02X}")
            print(f"Compression: {self.compression:02X}")
            print(f"Image Size: {self.image_size:02X}")
            print(f"X-PxPerMeter: {self.x_px_per_m:02X}")
            print(f"Y-PxPerMeter: {self.y_px_per_m:02X}")
            print(f"Colors: {self.colors:02X}")
            print(f"Important Colors: {self.important_color:02X}")

        if mode == PrintMode.INT:
            print(f"Size: {self.size}")
            print(f"Width: {self.width}")
            print(f"Height: {self.height}")
            print(f"Planes: {self.planes}")
            print(f"Bits per pixel: {self.bit_per_px}")
            print(f"Compression: {self.compression}")
            print(f"Image Size: {self.image_size}")
            print(f"X-PxPerMeter: {self.x_px_per_m}")
            print(f"Y-PxPerMeter: {self.y_px_per_m}")
            print(f"Colors: {self.colors}")
            print(f"Important Colors: {self.important_color}")

class Color:
    def __init__(self, data:bytes):
        self.blue = Utils.read_bytes(data, 1, 0)
        self.green = Utils.read_bytes(data, 1, 1)
        self.red = Utils.read_bytes(data, 1, 2)
        self.alpha = Utils.read_bytes(data, 1, 3)

class ColorTable:
    MEMORY_RANGE = (54, 118)

    def __init__(self, data:bytes) -> None:
        if not Utils.validate_data_length(data, self.MEMORY_RANGE):
            print("Header must be {0} bytes!".format(self.MEMORY_RANGE[1]))
            print("Finishing read with an error.")
            return
        
        self.table:list[Color] = []
        
        for i in range(0, 64, 4):
            temp_color = Color(data[0 + i:4 + i])
            self.table.append(temp_color)

    def to_bytes(self) -> bytes:
        return b''.join([
            Utils.write_bytes(color.blue, 1) + 
            Utils.write_bytes(color.green, 1) + 
            Utils.write_bytes(color.red, 1) + 
            Utils.write_bytes(color.alpha, 1)
            for color in self.table
        ])

    def print(self, mode:int) -> None:
        if mode == PrintMode.HEX:
            color_counter = 0
            for color in self.table:
                print(f"Color {color_counter}: B{color.blue:02X} G{color.green:02X} R{color.red:02X} A{color.alpha:02X}")
                color_counter += 1

        if mode == PrintMode.INT:
            color_counter = 0
            for color in self.table:
                print(f"Color {color_counter}: B{color.blue} G{color.green} R{color.red} A{color.alpha}")
                color_counter += 1

class Image:
    def __init__(self, data:bytes):
        self.pixels = [bytes([b]) for b in data]
        #mutable = bytearray(self.pixels[0])
        #mutable[0] = 0x00
        #self.pixels[0] = bytes(mutable)

    def __remap_pixel_nibble(self, nibble:int) -> int:
        remap_table = {
            0x0: 0x0F,
            0x1: 0x08,
            0x2: 0x07,
            0x3: 0x00
        }
        return remap_table.get(nibble, nibble)

    def __remap_image_bytes(self) -> None:
        self.remapped = bytearray()
        for byte in self.pixels:
            byte_val = byte if isinstance(byte, int) else byte[0]
            high = self.__remap_pixel_nibble(byte_val >> 4)
            low = self.__remap_pixel_nibble(byte_val & 0x0F)
            self.remapped.append((high << 4) | low)
            self.pixels = bytes(self.remapped)

    def __calculate_padding(self, width:int) -> int:
        row_bytes = (width + 1) // 2
        return (4 - (row_bytes % 4)) % 4 

    def add_padding(self, width:int, height:int) -> None:
        padded = bytearray()
        row_bytes = (width + 1) // 2
        padding = self.__calculate_padding(width)


        for i in range(height):
            start = i * row_bytes
            end = start + row_bytes
            row = self.pixels[start:end]
            padded.extend(b''.join(row))
            padded.extend(b'\x00' * padding)

        self.pixels = bytes(padded)

    def to_bytes(self):
        self.__remap_image_bytes()
        #return b"".join(self.pixels)
        return self.pixels

class Bitmap:
    def __init__(self, data:bytes):
        self.header = Header(data[slice(*Header.MEMORY_RANGE)])
        self.info_header = InfoHeader(data[slice(*InfoHeader.MEMORY_RANGE)])
        self.color_table = ColorTable(data[slice(*ColorTable.MEMORY_RANGE)])
        self.image = Image(data[ColorTable.MEMORY_RANGE[1]:])

    def to_bytes(self) -> bytes:
        #self.image.add_padding(self.info_header.width, self.info_header.height)
        return(
            self.header.to_bytes() +
            self.info_header.to_bytes() + 
            self.color_table.to_bytes() +
            self.image.to_bytes()
        )

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-m", "--mode", type=str, default="", help="script mode")
    parser.add_argument("-bf", "--base_file", type=str, default="", help="bmp base")
    parser.add_argument("-if", "--input_file", type=str, default="", help="bmp input")
    parser.add_argument("-of", "--output_file", type=str, default="", help="bmp output")

    args = parser.parse_args()

    if args.mode == "":
        print("Invalid file name!")
        sys.exit()

    if args.input_file == "":
        print("Invalid file name!")
        sys.exit()


    img_input = open(args.input_file, "rb")
    input_data = img_input.read()
    input_bmp = Bitmap(input_data)

    # Script in conversion mode requires base bitmap and output filename
    if args.mode == "c":
        if args.base_file == "":
            print("Invalid file name!")
            sys.exit()

        if args.output_file == "":
            print("Invalid file name!")
            sys.exit()

        img_base = open(args.base_file, "rb")
        img_output = open(args.output_file, "wb")

        base_data = img_base.read()

        base_bmp = Bitmap(base_data)
        output_bmp = Bitmap(input_data)

        output_bmp.info_header.colors = base_bmp.info_header.colors
        output_bmp.info_header.important_color = base_bmp.info_header.important_color
        output_bmp.color_table.table = base_bmp.color_table.table

        img_output.write(output_bmp.to_bytes())

        img_base.close()
        img_output.close()

    # Script in analyze mode just requires input bitmap
    if args.mode == "a":
        print(8*"-" + "Header:" + 8*"-")
        input_bmp.header.print(PrintMode.HEX)
        print(8*"-" + "Info Header:" + 8*"-")
        input_bmp.info_header.print(PrintMode.HEX)
        print(8*"-" + "Color table:" + 8*"-")
        input_bmp.color_table.print(PrintMode.HEX)

    img_input.close()
    
