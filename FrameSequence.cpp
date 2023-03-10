/**
 * Yelanika Gunasekara
 * GNSSEN002
 * FrameSequence.cpp
 * This is the source file implements the methods of the FrameSequence class.
 * **/

#include "FrameSequence.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <cmath>
 
namespace GNSSEN002 {

   /***
     * Default Constructor:
     * Instantiates neccessary variables. 
     * 
     * **/
    FrameSequence::FrameSequence(void) : row(0), col(0), mImage(nullptr), imageSequence(), height(0) {}

    /***
     * 
     * Custom Constructor
     * 
     * **/
    //FrameSequence::FrameSequence(int row, int col, unsigned char **mImage, std::vector<unsigned char **> imageSequence, int height) : row(row), col(col), mImage(nullptr), imageSequence(), height(height) {}

    /***
     * 
     * This function reads the pgm file in binary and gets the total rows and columns of the 
     * file.
     * The function returns bool value:
     *  - true - if file read completely
     *  - false - if file is not read or not read completely
     * 
     * **/ 
    bool FrameSequence::getImageDimensions(std::string pgmFile) {
 
        std::ifstream in(pgmFile, std::ios::in | std::ios::binary);
        std::string checkDigitStr = "";
        bool Dimensions = false;
        
        std::string p5;
        std::string twofivefive;
        std::string temp;     
 
        //Error checking: if the file does not exist or fails to open
        if (!in) {
            std::cerr << "File failed to open." << std::endl;
        }
        //if the file opens/exists, the data in the file is extracted
        else {
 
            std::getline(in, p5);
            std::getline(in, temp);

            if (temp.at(0) == '#') {
                while (!Dimensions) {
                    std::getline(in, temp);                
                    if (temp.at(0) == '#') 
                        Dimensions = false;
                    else    
                        Dimensions = true;
                }
            }                    
                  
            std::istringstream iss(temp);
            iss >> col >> std::ws >> row;
 
            in >> twofivefive >> std::ws;
 
            mImage = new unsigned char*[row];
            for (int i =0; i < row; ++i) {
                    
                mImage[i] = new unsigned char[col];
                for (int j =0; j < col; ++j ) {
                    in.read((char*)&mImage[i][j],1);
                }
            }

            return true;
        }

        return false;
    }

    /***
     * 
     * This function writes to the imageSquence pointer.
     * The various -w flag operations are implmented.
     * Files are proudced using imageSequence, per frame in the frame trajectory.
     * 
     * **/
    void FrameSequence::tracjectory(std::vector<int> x, std::vector<int> y, int width, int height, std::string operation, std::string name) { 
       
        for (int d = 0; d < x.size()-1; d++ ) {
            
            //calculating the new points of the frame 
            int x1 = x[d];
            int x2 = x[d+1];
            
            int y1 = y[d];
            int y2 = y[d+1];
            // std::cout << "x1: " << x1 << " x2: " << x2 << std::endl;
            // std::cout << "y1: " << y1 << " y2: " << y2 << std::endl;
            //Calculating the threshold 
            float g = ((float)(y2-y1))/((float)(x2-x1));
            int op = 0;
    
            if (operation.compare("none") == false) {       //Using operations from input - to decide which functions to implement
                op=1;
            }
            else if (operation.compare("invert") == false) {
                op=2;
            }
            else if (operation.compare("reverse") == false) {
                op=1;
            }
            else if (operation.compare("revinvert") == false) {
                op=2;
            }

            float ystart = y1;
            //int slope = 0;

            if (std::fabs(g) < 1.0) {           //if the absolute value of the threshold is smaller than 1

                if (x2 < x1) {
                    for (int x=x1; x >= x2; x--) {       
                        ystart = ystart + g; 
                        switch (op) {
                            case 1: { 
                                FrameSequence::none(x, std::round(ystart), width, height);
                                break;
                            }
                            case 2: {
                                FrameSequence::invert(x, std::round(y1), width, height);
                                break;
                            }
                        };
                    }
                }
                else{
                    for (int x=x1; x < x2; x++) {       
                        ystart = ystart + g; 
                        switch (op) {
                            case 1: { 
                                FrameSequence::none(x, std::round(ystart), width, height);
                                break;
                            }
                            case 2: {
                                FrameSequence::invert(x, std::round(y1), width, height);
                                break;
                            }
                        };
                    }

                }


            }
            else {          //if the asbsolute value of the threshold is greater than 1 
                if (y2 < y1) {
                    for (int y=y1; y >= y2; y--) {
                        x1+=(1/g);
                        switch (op) {
                            case 1: { 
                                FrameSequence::none(std::round(x1), y, width, height);
                                break;
                            }
                            case 2: {
                                FrameSequence::invert(std::round(x1), y, width, height);
                                break;
                            }
                        };
                    }
                }
                else {
                    for (int y=y1; y < y2; y++) {
                        x1+=(1/g);
                        switch (op) {
                            case 1: { 
                                FrameSequence::none(std::round(x1), y, width, height);
                                break;
                            }
                            case 2: {
                                FrameSequence::invert(std::round(x1), y, width, height);
                                break;
                            }
                        };
                    }
                }
            }
        }
        //Using operations from input - to decide which functions to implement
        if (operation.compare("none") == false) {
            FrameSequence::printImage(width,height, name);
        }
        else if (operation.compare("invert") == false) {
            FrameSequence::printImage(width,height, name);          
        }
        else if (operation.compare("reverse") == false) {
            FrameSequence::reversePrintImage(width,height, name);
        }
        else if (operation.compare("revinvert") == false) {
            FrameSequence::reversePrintImage(width,height, name);
        }
        
    }

    /***
     * 
     * the none -w flag method is implmented here.
     * The frame is added to imageSequence.
     * 
     * **/ 
    void FrameSequence::none(int x, int y, int width, int height) {
 
        unsigned char ** tracP = nullptr;
 
        int xCount = x;
        int yCount = y;
        tracP = new unsigned char*[height];
        for (int i = 0; i < height; ++i) {
            xCount++;
            tracP[i] = new unsigned char[width];
            for (int j =0; j < width; ++j ) {
                yCount++;
                tracP[i][j] = (unsigned char) mImage[xCount][yCount];                              
            }
            yCount =y;
        }
 
        imageSequence.push_back(tracP);
    }
 
    /***
     * 
     * The -w flag invert method is implmented here.
     * The frame is added to imageSequence.
     * 
     * **/
    void FrameSequence::invert(int x, int y, int width, int height) {
        
        std::cout << "ERROR" << std::endl;
        unsigned char ** tracP = nullptr;
 
        int xCount = x;
        int yCount = y;
        tracP = new unsigned char*[height];
        for (int i = 0; i < height; ++i) {
            xCount++;
            tracP[i] = new unsigned char[width];
            for (int j =0; j < width; ++j ) {
                yCount++;
                int p = 255;
                int pixel = 255 - (int)(mImage[xCount][yCount]);
                int * ptr = nullptr;
                ptr = &pixel;

                unsigned char * chptr = (unsigned char *)ptr;
 
                tracP[i][j] = *chptr;                              
            }
            yCount =y;
        }
 
        imageSequence.push_back(tracP);
    }
 
    /***
     * 
     * The -w flag reverse is printed here.
     * Each frame is extracted in reverse and the files are labelled accordingly.
     * The frames are extracted from imageSequence.
     * 
     * **/
    void FrameSequence::reversePrintImage(int width, int height, std::string name) {
 
        std::ofstream out;  
        int fnew =0;
        for (int f = imageSequence.size()-1; f >=0; f--) {
 
            std::string fnum = std::to_string(fnew);
            int flen = fnum.length();
            std::string temp;
            
            if (flen < 5) {     //allocating that the name of the file should be 4 values
                int dif = 4 - flen;
                for (int w = 0; w < dif; w++) {
                    temp += "0";
                }
                fnum = temp + fnum;
            }

            std::string filename = name + fnum + ".pgm";
            out.open(filename, std::ios::out | std::ios::binary);
            out << "P5" << std::endl;
            out << width << " " << height << std::endl;
            out << "255" << std::endl;
            
            for (int i = 0; i < height; ++i) {
                for (int j =0; j < width; ++j ) {
        
                    unsigned char * ptr = nullptr;
                    ptr = &imageSequence[f][i][j];
                    out.write((char *)ptr,1);              
                }
            }
 
            out.close();
            fnew++;
        };
        std::cout << "reverse Print Image: before" << std::endl;
        int isSize = imageSequence.size();
        for (int h = 0; h < isSize; ++h) {
            for (int r = 0; r < height; r++) {
                for (int w = 0; w < width; ++w)
                    imageSequence[h][r][w] = 0;
                imageSequence[h][r] = nullptr; 
                    
            }
            imageSequence.pop_back();
        }
        std::cout << "reverse Print Image: after" << std::endl;
        std::cout << imageSequence.size() << std::endl;
 
    }    
 
    /***
     *
     * Each frame is extracted and the files are labelled accordingly.
     * The frames are extracted from imageSequence.
     * 
     * ***/
    void FrameSequence::printImage(int width, int height, std::string name) {
       
        std::ofstream out;  
 
        for (int f =0; f < imageSequence.size(); f++) {
 
            std::string fnum = std::to_string(f);
            int flen = fnum.length();
            std::string temp;
            
            if (flen < 5) {
                int dif = 4 - flen;
                for (int w = 0; w < dif; w++) {
                    temp += "0";
                }
                fnum = temp + fnum;
            }

            std::string filename = name + fnum + ".pgm";
            out.open(filename, std::ios::out | std::ios::binary);
            out << "P5" << std::endl;
            out << width << " " << height << std::endl;
            out << "255" << std::endl;

            for (int i = 0; i < height; ++i) {
                for (int j =0; j < width; ++j ) {
 
                    unsigned char * ptr = nullptr;
                    ptr = &imageSequence[f][i][j];
                    out.write((char *)ptr,1);              
                }
            }
 
            out.close();
        }
        std::cout << "Print Image: before" << std::endl;
        int isSize = imageSequence.size();
        for (int h = 0; h < isSize; ++h) {
            for (int r = 0; r < height; r++) {
                for (int w = 0; w < width; ++w)
                   imageSequence[h][r][w] = 0;

                imageSequence[h][r] = nullptr;
            }
            imageSequence.pop_back();
        }
        std::cout << "Print Image: after" << std::endl;
        std::cout << imageSequence.size() << std::endl;
    }
 
    // /**
    //  * Destructor.
    //  * 
    //  * **/
    FrameSequence::~FrameSequence() {
        for (int i = 0; i < row; ++i) {
            delete [] mImage[i];
        }
        delete [] mImage;

        int isSize = imageSequence.size();
        for (int h = 0; h < isSize; ++h) {
            for (int r = 0; r < height; r++) {
                delete [] imageSequence[h][r];
            }
        }
    }
    
}
