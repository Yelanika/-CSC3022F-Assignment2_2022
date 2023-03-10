/***
 * Yelanika Gunasekara
 * GNSSEN002
 * extractor.cpp
 * This is the driver file.
 * It extracts the data from the command line and calls methods from the FrameSequence class.
 * 
 * ***/

#include "FrameSequence.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string> 

//here *argv[] is an array of pointers pointing to command line
int main (int argc, char *argv[]) {

    //the file that will be read
    std::string pgmFile = "";
    pgmFile = argv[1];

    //the size of the frame for tracjectory 
    int width = 0;
    int height = 0;

    //the x and y coordinates that indicate the frame tranjectories
    std::vector<int> x;
    std::vector<int> y;

    //operation that will be performed on the frame/pixel and it's name
    std::vector<std::string> operation;
    std::vector<std::string> name;
    
    //Temp x and y holding variables
    int xV = 0;
    int yV = 0;

    //if no parameters are entered at runtime, an error meesage will print
    if (argc == 1) {
        std::cerr << "No parameters entered" << std::endl;
    }
    // when parameters are entered, they will be read here
    else {

        int e = 2;
        while (e < argc) {
            std::string flag = "";
            std::istringstream iss(argv[e]);
            iss >> flag;
            
            //if the -p flag is found 
            if (flag.compare("-p") == 0){
                int n = 0;
                e++;
                std::istringstream iss4(argv[e]);
                iss4 >> n;

                for (int s = 0; s < n; s++) {
                    e++;
                    std::istringstream iss2(argv[e]);
                    iss2 >> xV;
                    if (xV < 0) {           //Error Check
                        std::cout << "The frame co-ordinates you have entered is incorrect. Please try again.";
                        return 0;
                    }
                    else                    
                        x.push_back(xV);

                    e++;
                    std::istringstream iss3(argv[e]);
                    iss3 >> yV;
                    if (yV < 0) {           //Error Check
                        std::cout << "The frame co-ordinates you have entered is incorrect. Please try again.";
                        return 0;
                    }
                    else 
                        y.push_back(yV);
                }
                
            }
            //if the -t flag is found
            else if (flag.compare("-t") == 0) {
                for (int s = 0; s < 2; s++) {

                    e++;
                    std::istringstream iss2(argv[e]);
                    iss2 >> xV;
                    if (int(xV) < 0) {          //Error Check
                        std::cout << "The frame co-ordinates you have entered is incorrect. Please try again." << std::endl;
                        return 0;
                    }
                    else 
                        x.push_back(xV);

                    e++;
                    std::istringstream iss3(argv[e]);
                    iss3 >> yV;
                    if (yV < 0) {       //Error Check
                        std::cout << "The frame co-ordinates you have entered is incorrect. Please try again." << std::endl;
                        return 0;
                    }
                    else 
                        y.push_back(yV);
                }
            }

            //the -s flag data is read
            e++;

            e++;
            std::istringstream iss2(argv[e]);
            iss2 >> width;

            e++;
            std::istringstream iss3(argv[e]);
            iss3 >> height;

            //Error checking the width and height of frame 
            if ((height < 0) || ( width < 0)) {
                std::cout << "The frame size you have entered is incorrect. Please try again." << std::endl;
                return 0;
            }

            //the -w flag data is read
            for (int s = e; s < argc; s++ ) {
                e++;
                std::string temp;
                e++;
                std::istringstream iss5(argv[e]);
                iss5 >> temp;
                operation.push_back(temp);

                e++;
                std::istringstream iss6(argv[e]);
                iss6 >> temp;
                name.push_back(temp);
            }

        }

        //Invokes the default constructor 
        GNSSEN002::FrameSequence FSObject;
        //Calls the getImageDimensions Method which returns true if file copied completely else false
        bool gotFile = FSObject.getImageDimensions(pgmFile);

        //if file has been retrieved completely - continue with processing data 
        if (gotFile) {
            for (int i = 0; i < operation.size(); i++) {
                for (int k = 0; k < x.size(); ++k) {
                std::cout << "x: " << x[k] << std::endl;
                std::cout << "y: " << y[k] << std::endl;
                }
                
                FSObject.tracjectory(x,y,width,height, operation[i], name[i]);
            }
        } //else end program        
    }   

    return 0;

}