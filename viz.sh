#!/bin/sh

set -e

if [ $# -eq 0 ]; then
	echo "Usage: $0 <input.dot>"
 	exit 1
fi

input_file="$1"
output_svg="out.svg"
output_png="out.png"

dot -Tsvg "$input_file" > "$output_svg"
inkscape "$output_svg" -o "$output_png"