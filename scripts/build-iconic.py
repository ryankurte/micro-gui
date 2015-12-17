#!/usr/bin/env python3

from os import listdir
from os.path import isfile, join

import argparse
import re

from PIL import Image
import pystache


def process_image(filename):
	image = Image.open(args.folder[0] + '/' + filename)
	data = list(image.getdata())
	return filename.split('.')[0].replace('-', '_'), data

def generate_line(name, data):
	line = 'uint8_t ' + name + '[] = {' + data + '};'
	return line

def generate_data(data):
	data_array = []
	for a in data:
		data_array.append(hex(a[3]))
	return ', '.join(data_array)

def generate_file(template, name, data):
	print("Writing to output file: " + name)

	template_file = open(template, 'r')
	template = template_file.read()
	template_file.close()

	output_data = pystache.render(template, data)

	output_file = open(name, 'w')

	output_file.write(output_data)
	output_file.close()


# Setup arguments
parser = argparse.ArgumentParser(description='Process open-iconic png files to c sources')

parser.add_argument('--scale', nargs=1, type=int, default=1, 
                   help='icon scale, either 1, 2, 3, 4, 6, 8')

parser.add_argument('--folder', nargs=1, default=['./png'],
                   help='folder to look for icons')

parser.add_argument('--template', nargs=1, default=['icon-template.h'],
                   help='mustache template to fill')

parser.add_argument('--output', nargs=1, default=['icons.h'],
                   help='output file')

args = parser.parse_args()


# Create filter for scale setting
if args.scale[0] == 1:
	filter = re.compile('^([a-z\-]+).png')
else:
	filter = re.compile('^([a-z\-]+)-' + str(args.scale) + 'x.png')

# Parse folder
files = [f for f in listdir(args.folder[0]) if isfile(join(args.folder[0], f))]

# Filter files based on scale
filtered_files = [f for f in files if filter.match(f)]

file_data = {}

file_data['template'] = args.template[0]
file_data['scale'] = args.scale[0]
file_data['icons'] = []

for f in filtered_files:
	name, data = process_image(f)
	icon = {}
	icon['name'] = name
	icon['data'] = generate_data(data)
	icon['size'] = len(data)
	file_data['icons'].append(icon)

generate_file(args.template[0], args.output[0], file_data)
