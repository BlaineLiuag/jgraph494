QR_Create: QR Code Generator Using JGraph
-----------------------------------------
QR_Create is a shell script which must take a single
argument as the intended output file.

QR_Create will prompt the user for information related
to their intended code generation and desired appearance.

QR_Create will take from stdin user input and generate a
png file which contains the qr code.

Usage:

	sh QR_Create outfile.png

	Input String: Any input string intended for encoding.
	Design Type: User can select between solid (non-patterned)
				 design, horizontal stripes, vertical stripes,
				 or diagonal stripes.
	Colors: User inputs a series of triple <1 floats indicating the
			number of colors desired for use in encoding.
			For solid designs, mutli-color input will be distributed
			randomly among the pixels.
			For horizontal, vertical, and diagonal stripes the color
			will be passed along in an organizational manner.
	Center Image: .pse image which can be pasted onto the front center
				  of the qr code. Size of the image will likely not
				  exceed that which is capable of being managed by
				  inborn error correction.

Example Runtime:

	>sh QR_Create outfile.png
	
	QR Code Generator
	Please provide input string: 

	>Hello World

	Specify Design Type
	Solid/H_Stripe/V_Stripe/D_Stripe

	>Solid

	Select Colors:
	
	>0 1 0 0 0 1

	Center Image (none/image.eps):

	>centeredimg.eps

	Conversion Complete


Compiling:

	From main directory type
	 
		>make

	From subdirectory "jgraph"

		>make
	
	The shell script presumes that you are using
	the jgraph executable found in subdirectory jgraph.
	Be sure to compile from jgraph subdirectory to ensure
	correct encodings.


Demo:

	>make run-demo

	Can be called after compilation which will generate five different
	QR code encodings to be used.

