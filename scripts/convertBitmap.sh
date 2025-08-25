#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BITMAP_DIR="${SCRIPT_DIR}/../bitmap"

while getopts ":i:o:s:h" option; do
   case "${option}" in
        h) 
            echo "Help:"
            echo "-i <input_image_filename>, e.g. -i i.jpeg"
            echo "-o <output_bitmap_name>, e.g. -o a.bmp"
            echo "-s <image_size>, e.g. -s 100x100"
            ;;
        i)
            INPUT_FILE=${OPTARG}
            ;;
        o)
            OUTPUT_FILE=${OPTARG}
            ;;
        s)
            IMAGE_SIZE=${OPTARG}
            ;;
   esac
done

echo "Converting ${BITMAP_DIR}/${INPUT_FILE} ..."

convert ${BITMAP_DIR}/${INPUT_FILE} \
        -colorspace gray +matte \
        -colors 4 \
        -depth 8 \
        -units PixelsPerInch \
        -density 72x72 \
        -resize "${IMAGE_SIZE}>" \
        BMP3:${BITMAP_DIR}/${OUTPUT_FILE}


echo "Convertion complete!"
echo "${BITMAP_DIR}/${OUTPUT_FILE} ..."