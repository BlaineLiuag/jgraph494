#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <cstring>
#include <sstream>
#include <random>
using namespace std;

//Initializes jgraph to adequate dimensions.
//Parameters:
//	Output filestream to jgraph file
//	integer x-axis length of jgraph plot
//	integer y-axis length of jgraph plot
void jgraph_init(ofstream& Jgraph, int X, int Y){
	
	Jgraph << "newgraph\n";
	Jgraph << "xaxis nodraw" << endl; //min 0 max " << X << endl;
	Jgraph << "yaxis nodraw" << endl; //min 0 max " << Y << endl;

}

//Outputs our square graph arrangement to jgraph.
//Parameters:
//	Output filestream to jgraph file.
//	integer vector of x-axis square position
//	integer vector of y-axis square position
//	vector triple desired colors
//		- Color scheme for solid graph is singular
//		  or if multiple colors passed then
//		  design is randomized.
void jgraph_solid(ofstream& Jgraph, vector<vector<int>> graph, vector<tuple<float, float, float>> colors){

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, colors.size()-1);
	int size = graph.size();

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(graph[i][j] == 1){
				int color = dist(gen);
				float r = get<0>(colors[color]);
				float g = get<1>(colors[color]);
				float b = get<2>(colors[color]);
				Jgraph << "newline poly pcfill " << r
				<< " " << g << " " << b << " color " << r << " "
				<< g << " " << b << " pts "
				<< i << " " << j << "  " 
				<< i+1 << " " << j << "  "
				<< i+1 << " " << j+1 << "  "
				<< i << " " << j+1 << endl;
			}
		}
	}
}

//Outputs QR code arrangement, horizontal color scheme
//Parameters:
//	Output file stream
//	integer vector of x-axis squares
//	integer vector of y-axis squares
//	vector triple of desired colors
//		- Colors on H_stripe are in order and evenly
//		  distributed.
void jgraph_Hstripe(ofstream& Jgraph, vector<vector<int>> graph, vector<tuple<float, float, float>> colors){

	for(int i = 0; i < (int) graph.size(); i++){
		for(int j = 0; j < (int) graph.size(); j++){
			if(graph[i][j] == 1){
				
				int color = j%colors.size();
				
				float r = get<0>(colors[color]);
				float g = get<1>(colors[color]);
				float b = get<2>(colors[color]);
				Jgraph << "newline poly pcfill " << r
				<< " " << g << " " << b
				<< " color " << r << " " << g << " "
				<< b << " pts "
				<< i << " " << j << "  " 
				<< i+1 << " " << j << "  "
				<< i+1 << " " << j+1 << "  "
				<< i << " " << j+1 << endl;
			}
		}
	}
}

//Outputs QR code arrangement, vertical color scheme
//Parameters:
//	Output file stream
//	integer vector of x-axis squares
//	integer vector of y-axis squares
//	vector triple of desired colors
//		- Colors on V-stripe are printed in order
//		  and are evenly distributed
void jgraph_Vstripe(ofstream& Jgraph, vector<vector<int>> graph, vector<tuple<float, float, float>> colors){

	for(int i = 0; i < (int) graph.size(); i++){
		for(int j = 0; j < (int) graph.size(); j++){
			if(graph[i][j] == 1){

				int color = i%colors.size();
				
				float r = get<0>(colors[color]);
				float g = get<1>(colors[color]);
				float b = get<2>(colors[color]);
				Jgraph << "newline poly pcfill " << r
				<< " " << g << " " << b
				<< " color " << r << " "
				<< g << " " << b << " pts "
				<< i << " " << j << "  " 
				<< i+1 << " " << j << "  "
				<< i+1 << " " << j+1 << "  "
				<< i << " " << j+1 << endl;
			}
		}
	}

}

//Outputs QR code arrangement with diagonal color stripes
//Parameters:
//	Output file stream
//	integer vector of x-axis squares
//	integer vector of y-axis squares
//	vector triple of desired colors
void jgraph_Dstripe(ofstream& Jgraph, vector<vector<int>> graph, vector<tuple<float, float, float>> colors){
	for(int i = 0; i < (int) graph.size(); i++){
		for(int j = 0; j < (int) graph.size(); j++){
			if(graph[i][j] == 1){

				int color = (i+j)%colors.size();
				int stripe = (i+j+1)%colors.size();
				float r = get<0>(colors[color]);
				float g = get<1>(colors[color]);
				float b = get<2>(colors[color]);
				float sr = get<0>(colors[stripe]);
				float sg = get<1>(colors[stripe]);
				float sb = get<2>(colors[stripe]);
				Jgraph << "newline poly color " << r << " "
				<< g << " " << b << " pcfill " << sr << " "
				<< sg << " " << sb << " ppattern stripe 60 pts "
				<< i << " " << j << "  " 
				<< i+1 << " " << j << "  "
				<< i+1 << " " << j+1 << "  "
				<< i << " " << j+1 << endl;
			}
		}
	}

}

//Centers an image onto the QR code output
//Parameters:
//	Output file stream
//	integer size of the square code
//	name of .eps file image is taken from
void center_img(ofstream& Jgraph, int size, string image){
	
	//Determine center of QR Code
	// - Center of QR code should be 1/3 in from the
	//   beginning.
	
	float cube = (float) size/4;
	float center = (float) size/2;
	Jgraph << "newcurve eps " << image << " marksize " << cube << " " << cube << " pts "
		   << center << " " << center << endl;
}


int main(int argc, char *argv[]){
    
	if(argc < 2){
		cout << "Usage: PPM DESIGN COLORS DECAL OUTFILE" << endl;
		exit(1);
	}
	ifstream ppmFile(argv[1]);
	if (!ppmFile) {
		cerr << "Error opening PPM file." << endl;
		exit(1);
	}
	ofstream jgrFile(argv[argc-1]);
	
	
	//take input from ppm file -----------------------
	
	int X; //X and Y dimensions of graph
	int Y;
	ppmFile >> X >> Y >> ws;
	//cout << X << " " << Y << endl;

	vector<vector<int>> graph; //block positions on code
	vector<int> tmp;
	string line;
	
	for(int i = 0; i < Y; i++){
		getline(ppmFile, line);
		for(int j = 0; j < X; j++) {
			if(line[j] == '1'){
				tmp.push_back(1);

            }
			else{
				tmp.push_back(0);
			}
        }
		graph.push_back(tmp);
		tmp.clear();
    }

	//Initialize jgraph
	jgraph_init(jgrFile, X, Y);

	//Parse color input
	vector<tuple<float, float, float>> Colors;
	string color_str = argv[3];
	stringstream ss(color_str);
	float r, g, b;
	while(ss >> r >> g >> b){
        Colors.push_back(make_tuple(r, g, b));
    }
	
	//Draw image according to design
	if(strcmp(argv[2], "Solid") == 0){
		jgraph_solid(jgrFile, graph, Colors);
	}
	else if(strcmp(argv[2], "H_Stripe") == 0){
		jgraph_Hstripe(jgrFile, graph, Colors);
	}
	else if(strcmp(argv[2], "V_Stripe") == 0){
		jgraph_Vstripe(jgrFile, graph, Colors);
	}
	else if(strcmp(argv[2], "D_Stripe") == 0){
		jgraph_Dstripe(jgrFile, graph, Colors);
	}

	//Add a center image if needed.
	if(strcmp(argv[argc-2], "none") != 0){
		center_img(jgrFile, X, argv[argc-2]);
	} 

    return 0;
}
