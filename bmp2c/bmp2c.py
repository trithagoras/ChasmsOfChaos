from PIL import Image, UnidentifiedImageError
import argparse
import os
import re
import jinja2

template = jinja2.Template('''#pragma once
#include <vector>
/*
	These files are autogenerated using the bmp2c tool.
	Do not edit this file directly.
*/

const std::vector<std::vector<uint32_t>> {{name}} = { {
	{{values}}
} };
''')                                                      

def sanitize_identifier(identifier):
    sanitized = re.sub(r'[^0-9a-zA-Z_]', '_', identifier)
    if re.match(r'^\d', sanitized):
        sanitized = '_' + sanitized
    return sanitized

def get_colors(inPath: str):
    try:
        aa = []
        img = Image.open(inPath)
        img = img.convert('RGB')
        for row in range(0, img.height):
            a = []
            for col in range(0, img.width):
                r, g, b = img.getpixel((col, row))
                a.append(f'0x{r:02X}{g:02X}{b:02X}')
            aa.append(a)
        return aa
    except UnidentifiedImageError:
        print('Error: Could not identify image file')
        exit(1)

def main(inPath: str, outPath: str | None):
    if outPath is None:
        outPath = os.path.splitext(inPath)[0] + '.h'
    
    a = get_colors(inPath)
    print(outPath)
    with open(outPath, "w") as f:
        filename = os.path.splitext(os.path.basename(inPath))[0]
        filename = sanitize_identifier(filename)
        height = len(a)
        width = len(a[0])
        f.write(template.render(name=filename, values=',\n\t'.join([f'{{ {", ".join(row)} }}' for row in a])))
        
    
if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='convert a BMP image to a C header file')
    parser.add_argument(
        'path', metavar='path', type=str,
        help='the path to the BMP file to convert')
    parser.add_argument(
        '--out', '-o', metavar='path', type=str,
        help='the path to the output C header file'
    )
    args = parser.parse_args()
    main(args.path, args.out)