#! /usr/bin/env python3

from PIL import Image
from bitarray import bitarray
import re

png = Image.open("lsb_RGB.png")
pixels = png.load()

print("dimensions: {}x{}".format(png.width, png.height))
print("max octets dissimulés: {}".format((png.width * png.height * 3) // 8))

data = bitarray()
# parcourt les pixels en y puis x
for x in range(png.width):
    for y in range(png.height):
        r, g, b = pixels[x, y]
        # extrait le bit 0 de la composante R, puis G, puis B
        data.append(r & 1)
        data.append(g & 1)
        data.append(b & 1)

# matche le début des sorties de xxd
xxd_pattern = re.compile(rb'[0-9a-f]{8}: .*')

# convertit les lignes du dump hexadécimal
extracted = bytearray()
for line in data.tobytes().split(b'\n'):
    if len(line) <= 67 and xxd_pattern.match(line):
        extracted.extend(bytearray.fromhex(line[10:49].decode()))

# écrit les octets extraits
with open("extract.bin", "wb") as fp:
    fp.write(extracted)

print("extraction: {} octets".format(len(extracted)))
