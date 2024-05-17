/* QRGenerator.cpp
 * Source code file for generating
 * QR code "ppm" files based off
 * of a string literal input.
 */

#include <string>
#include <vector>
#include <iostream>
#include "qrcodegen.hpp"
using namespace qrcodegen;

int main(int argc, char *argv[]){
	
	const QrCode qr = QrCode::encodeText(argv[1], QrCode::Ecc::MEDIUM);
	int size = qr.getSize();
	
	std::cout << size << " " << size << std::endl;
	for(int y = 0; y < size; y++){
		for(int x = 0; x < size; x++){
			if(qr.getModule(x, y)){
				std::cout << 1;
			}
			else{
				std::cout << 0;
			}
		}
		std::cout << std::endl;
	}

	return 0;
}
