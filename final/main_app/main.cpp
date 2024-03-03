//Written by Panagiotis Panagiotou, 3180139 
//First, include all the libraries we made whice we're going to use
#include "../image.h" 
#include "../filterLinear.h"
#include "../filterGamma.h"
#include "../vec3.h"
//Then, include all the header files of the language needed for the application to work
#include <string>
#include <iostream> 
#include <vector> 
#include <stdlib.h>
#include <stdio.h>
#define Color math::Vec3<float>
using namespace image; //all the image and filter header files were implemented in this namespace
int main(int argc, char* argv[]) {
	Image picture = Image(); //create an empty image object
	int i = 0;
	int size = argc; //save the amount of arguments of the command line
	i = 1;
	std::string file_name(argv[size - 1]); //get the name of the file.
	if (picture.load(file_name, "ppm")) {
		std::cout << "Picture " + file_name + " was loaded succesfully.\n";
	}
	else {
		std::cout << "Picture " + file_name + " could not be loaded.\n";
		return 0;
	}
	while (i < size) {
		std::string check_f(argv[i]); //check if there's a filter on the way
		if (check_f == "-f") {	//if there is , check wheter it's a linear or gamma filter
			std::string check_filter(argv[i + 1]);//get the filter type as a string
			if (check_filter == "gamma") {	//if the filter is gamma
				i = i + 2; 
				float gamma_number = (float)atof(argv[i]);	//get the float that represenets the gamma number
				FilterGamma temp_filter = FilterGamma(gamma_number); //create a new gamma filter object
				picture = temp_filter << picture; // apply the filter to the current picture
				std::cout << "A Gamma filter was applied to the picture.\n";
				i++;
			}
			else if (check_filter == "linear") {
				i = i + 2;
				float a1 = (float)atof(argv[i]); //get the firt parameter of a 
				i++;
				float a2 = (float)atof(argv[i]); //get the second parameter of a
				i++;
				float a3 = (float)atof(argv[i]); //get the third parameter of a
				i++;
				float c1 = (float)atof(argv[i]); //get the first parameter of c 
				i++; 
				float c2 = (float)atof(argv[i]); //get the second parameter of c
				i++;
				float c3 = (float)atof(argv[i]); //get the third parameter of c
				Color a = Color(a1, a2, a3);//create a new math::vec3<float> that represents a
				Color c = Color(c1, c2, c3);//create a new math::vec3<float> that represents c
				FilterLinear temp_filter = FilterLinear(a, c);//create a new linear filter object
				picture = temp_filter << picture; // apply the filter to the current picture
				std::cout << "A Linear filter was applied to the picture.\n";
				i++;
			}
		}else{	//if all filters were applied, now it's time to save the picture to a new file.
			std::string new_file_name = "filtered_" + file_name; //the name of the new file
			if (picture.save(new_file_name, "ppm"))	//if the saving of picture happened succesfully, the function returns true
				std::cout << "The new image "+new_file_name+" has been saved.\n";
			else //if it returns false, that means that something is wrong with the file.
				std::cout << "The filtered image could not be saved.\n";
			i++;
		}
	}
	system("PAUSE"); //so the console doesn't close immediately
	return 0;
}