#!/bin/bash

# Check if an input was provided
echo "QR Code Generator"
echo "Please provide input string: "
read input_string
bin/QRGenerator "$input_string" > output.ppm

echo " "
echo "Specify Design Type"
echo "Solid/H_Stripe/V_Stripe/D_Stripe"
read design

echo " "
echo "Select Colors:"
read colors

echo " "
echo "Center Image (none/image.eps):"
read image

bin/JGgenerator output.ppm "$design" "$colors" "$image" output.jgr
jgraph/jgraph output.jgr > output.ps
ps2pdf -P output.ps output.pdf
convert output.pdf -trim -background white -alpha remove -alpha off "$1"
rm output.ppm output.jgr output.ps output.pdf
echo " "
echo "Conversion Complete"
