#include "FrameSequence.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

//here *argv[] is an array of pointers pointing to command line
int main (int argc, char *argv[]) {

    std::cout << "Main Func"<< std::endl;

    //the file that will be read
    std::string pgmFile = "";
    pgmFile = argv[1];

    //cordinates for the beginning and end of the frame tranjectory
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    //the size of the frame for tracjectory 
    int width = 0;
    int height = 0;

    //operation that will be performed on the frame/pixel and it's name
    std::vector<std::string> operation;
    std::vector<std::string> name;
    
    //if no parameters are entered at runtime, an error meesage will print
    if (argc == 1) {
        std::cerr << "No parameters entered" << std::endl;
    }
    // when parameters are entered, they will be read here
    else {

        //std::cout << argc << std::endl;

        for (int i = 0; i < 10; ++i) {
          //  std::cout << i << std::endl;
            std::istringstream iss(argv[i]);

            switch (i) {
                case 3: {
                    iss >> x1; 
                    break;
                }
                case 4: {
                    iss >> y1; 
                    break;
                }
                case 5: {
                    iss >> x2; 
                    break;
                }
                case 6: {
                    iss >> y2; 
                    break;
                }
                case 8: {
                    iss >> width; 
                    break;
                }case 9: {
                    iss >> height; 
                    break;
                }
            }
        }

        int i = 10;

        while (i < argc) {
            i++;

            operation.push_back(argv[i]);
            i++;;

            name.push_back(argv[i]);
            i++;
        }
        
    }

    GNSSEN002::FrameSequence FSObject; 
    FSObject.getImageDimensions(pgmFile);

    for (int i = 0; i < operation.size(); i++) {
        FSObject.tracjectory(x1,y1,x2,y2,width,height, operation[i], name[i]);
    }

    return 0;

}