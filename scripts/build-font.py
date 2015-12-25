#!/usr/bin/env python3

from os import listdir
from os.path import isfile, join

import argparse
import re
import string

from PIL import Image, ImageFont, ImageDraw
import pystache

def print_hex(val):
	return "{0:#0{1}x}".format(val,4)

def process_char(font, char):
	# Calculate char info
	char_size = font.getsize(char);
	char_mask = font.getmask(char);
	#Create image
	char_image = Image.new('1', char_size, 0);
	#Draw font to image
	d = ImageDraw.Draw(char_image);
	d.fontmode = '1';
	d.text((0, 0), char, font=font, fill=(1));
	return char_image;

def generate_bin_image(image):
	data = image.getdata();
	size = image.size;

	bin_image = [[0 for i in range(size[0])] for j in range(size[1])];

	for j in range(size[1]):
		for i in range(size[0]):
			index = j * size[0] + i;
			if data[index] == 0:
				bin_image[j][i] = '0';
			else:
				bin_image[j][i] = '1';

	return bin_image;

def bin_to_byte_data(min_width_bytes, min_height, image_bin):
	data = [];
	for i in range(0, len(image_bin)) :
		row = image_bin[i];
		row_data = []
		temp = '';
		for j in range(0, len(row)):
			temp += str(row[j]);
			if(len(temp) % 8 == 0):
				row_data.append(print_hex(int(temp, 2)));
				temp = '';
		if len(temp) > 0 :
			while len(temp) < 8:
				temp += '0';
			row_data.append(print_hex(int(temp, 2)));

		while len(row_data) < min_width_bytes:
			row_data.append(print_hex(0));

		data.append(row_data);

	while(len(data) < min_height):
		row_data = [print_hex(0) for i in range(0, min_width_bytes)];
		data.append(row_data)
	return data;

def bytes_to_string(image_bytes):
	data = '';
	for i in range(0, len(image_bytes)):
		data += ', '.join(image_bytes[i]) + ',\r\n';
	return data;


def generate_file(template, name, data):
	#print("Writing to output file: " + name)

	template_file = open(template, 'r')
	template = template_file.read()
	template_file.close()

	output_data = pystache.render(template, data)

	output_file = open(name, 'w')

	output_file.write(output_data)
	output_file.close()

# Setup arguments
parser = argparse.ArgumentParser(description='Process open-iconic png files to c sources')

parser.add_argument('--size', nargs=1, type=int, default=[16], 
                   help='font size')

parser.add_argument('--font', nargs=1, default=["../resources/RobotoMono-Regular.ttf"],
                   help='ttf font file to generate from')

parser.add_argument('--template', nargs=1, default=['font-template.c'],
                   help='mustache template to fill')

parser.add_argument('--output', nargs=1, default=['font.c'],
                   help='output file name')

parser.add_argument('--start', nargs=1, type=int, default=[32], 
                   help='start character')

parser.add_argument('--end', nargs=1, type=int, default=[127], 
                   help='end character')

# Parse arguments
args = parser.parse_args()

font_file = args.font[0];
font_path = font_file.split('/');
font_name = font_path[len(font_path) - 1].split('.')[0].replace('-', '_').lower();

font_size = args.size[0];

# Generate char list
chars = [chr(c) for c in range(args.start[0], args.end[0])];

font = ImageFont.truetype(font=font_file, size=font_size);

images = {};

# Generate character images
for c in chars:
	images[c] = process_char(font, c);

#print("Created: " + str(len(images)) + " sprites");

# Determine minimum height and width
min_width = 0;
min_height = 0;

for i in images:
	if min_width < images[i].size[0]:
		min_width = images[i].size[0];
	if min_height < images[i].size[1]:
		min_height = images[i].size[1];

#print("Minimum width: " + str(min_width) + " pixels");
#print("Minimum height: " + str(min_height) + " pixels");

# Calculate minimum common image width
min_width_bytes = int(min_width / 8);
if min_width % 8 != 0:
	min_width_bytes += 1;

# Generate image data
image_data = {};
for i in chars:
	image_data[i] = generate_bin_image(images[i]);

# Convert into bytes
image_bytes = {};
for i in chars:
	image_bytes[i] = bin_to_byte_data(min_width_bytes, min_height, image_data[i]);

# Generate character data strings
image_strings = {};
for i in chars:
	image_strings[i] = bytes_to_string(image_bytes[i]);

# Combine into structure for template use
template_data = {};
template_data['chars'] = [];
template_data['size'] = font_size;
template_data['name'] = font_name;
template_data['NAME'] = font_name.upper();
template_data['start'] = ord(chars[0]);
template_data['end'] = ord(chars[len(chars) - 1]);
template_data['count'] = args.end[0] - args.start[0];
template_data['char_height'] = min_height;
template_data['char_width'] = min_width_bytes;

for i in chars:
	char_data = {};
	
	char_data['char'] = i;
	char_data['code'] = ord(i);
	char_data['bin'] = image_data[i];
	char_data['byte'] = image_bytes[i];
	char_data['string'] = image_strings[i];
	char_data['width'] = images[i].size[0];
	char_data['height'] = images[i].size[1];

	template_data['chars'].append(char_data);

#print(template_data);

generate_file(args.template[0], args.output[0], template_data);
