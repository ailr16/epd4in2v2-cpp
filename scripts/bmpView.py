import struct
import numpy as np
import matplotlib.pyplot as plt

def read_bmp_4bit(filepath):
    with open(filepath, 'rb') as f:
        data = f.read()

    # --- Parse headers ---
    pixel_offset = struct.unpack_from('<I', data, 10)[0]
    width = struct.unpack_from('<I', data, 18)[0]
    height = struct.unpack_from('<I', data, 22)[0]
    bit_count = struct.unpack_from('<H', data, 28)[0]
    colors_used = struct.unpack_from('<I', data, 46)[0] or 16

    assert bit_count == 4, "Only 4-bit BMPs are supported"

    # --- Parse color table ---
    palette = []
    for i in range(colors_used):
        b, g, r, _ = struct.unpack_from('<BBBB', data, 54 + i * 4)
        palette.append((r, g, b))  # RGB format

    print(palette)

    # --- Parse pixel data ---
    row_size = ((width + 1) // 2 + 3) & ~3  # Each row is padded to 4 bytes
    pixels = []
    for y in range(height):
        row = []
        offset = pixel_offset + (height - 1 - y) * row_size
        for x in range(0, width, 2):
            byte = data[offset + x // 2]
            high = byte >> 4
            low = byte & 0x0F
            row.append(palette[high])
            if x + 1 < width:
                row.append(palette[low])
        pixels.append(row)

    return np.array(pixels, dtype=np.uint8)


def remap_4bit_grayscale(data, pixel_offset, width, height):
    row_size = ((width + 1) // 2 + 3) & ~3
    new_data = bytearray(data)

    for y in range(height):
        row_start = pixel_offset + (height - 1 - y) * row_size
        for x in range(0, width, 2):
            byte = data[row_start + x // 2]
            high = (byte >> 4) & 0x0F
            low = byte & 0x0F

            # Remap 0–3 to 0x00, 0x05, 0x0A, 0x0F
            remap = lambda v: [0x00, 0x05, 0x0A, 0x0F][v] if v < 4 else v
            new_byte = (remap(high) << 4) | remap(low)
            new_data[row_start + x // 2] = new_byte

    return new_data

# --- Load BMP ---
with open('output2.bmp', 'rb') as f:
    bmp_data = f.read()

# --- Parse header ---
pixel_offset = struct.unpack_from('<I', bmp_data, 10)[0]
width = struct.unpack_from('<I', bmp_data, 18)[0]
height = struct.unpack_from('<I', bmp_data, 22)[0]
bit_depth = struct.unpack_from('<H', bmp_data, 28)[0]

assert bit_depth == 4, "This script only works with 4-bit BMPs"

# --- Remap pixel data ---
remapped_data = remap_4bit_grayscale(bmp_data, pixel_offset, width, height)

# --- Save new BMP ---
with open('remapped.bmp', 'wb') as f:
    f.write(remapped_data)
"""
# --- Load and display ---
bmp_array = read_bmp_4bit('output.bmp')
plt.imshow(bmp_array)
plt.axis('off')
plt.title('Decoded BMP Image')
plt.show()
"""