#!/usr/bin/env python3

from os import listdir
from os.path import isfile, join

import argparse
import re

from PIL import Image

header = '#include <stdint.h>\r\n\r\n'

def process_image(filename):
	image = Image.open(args.folder + '/' + filename)
	
	data = list(image.getdata());

	return filename.split('.')[0], data

def generate_line(name, data):
	data_array = [];
	for a in data:
		data_array.append(str(a[3]))
	line = 'uint8_t ' + name + '[] = {' + ', '.join(data_array) + '};'
	return line

# Setup arguments
parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('scale', metavar='N', type=int, default=1, 
                           help='icon scale, either 1, 2, 3, 4, 6, 8')

parser.add_argument('--folder', nargs=1, default='./png',
                   help='folder to look for icons')

parser.add_argument('--output', nargs=1, default='outputs.c',
                   help='output file')

args = parser.parse_args()

# Create filter for scale setting
if args.scale == 1:
	filter = re.compile('^([a-z\-]+).png')
else:
	filter = re.compile('^([a-z]+)-' + str(args.scale) + 'x.png')

# Parse folder
files = [f for f in listdir(args.folder) if isfile(join(args.folder, f))]

# Filter files based on scale
filtered_files = [f for f in files if filter.match(f)];

file_data = []

print("Writing to output file: " + args.output)

output_file = open(args.output,'w')

output_file.write(header);

for f in filtered_files:
	name, data = process_image(f);
	line = generate_line(name, data)

	output_file.write(line + '\r\n')

output_file.close()
