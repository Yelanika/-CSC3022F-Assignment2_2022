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
                    x.push_back(xV);

                    e++;
                    std::istringstream iss3(argv[e]);
                    iss3 >> yV;
                    y.push_back(yV);
                }
                
            }
            //if the -t flag is found
            else if (flag.compare("-t") == 0) {
                for (int s = 0; s < 2; s++) {

                    e++;
                    std::istringstream iss2(argv[e]);
                    iss2 >> xV;
                    x.push_back(xV);

                    e++;
                    std::istringstream iss3(argv[e]);
                    iss3 >> yV;
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

        GNSSEN002::FrameSequence FSObject; 
        FSObject.getImageDimensions(pgmFile);


        // for (int i = 0; i < operation.size(); i++) {        
        //     FSObject.tracjectory(x,y,width,height, operation[i], name[i]);
        // }

        
    }   

    return 0;

}