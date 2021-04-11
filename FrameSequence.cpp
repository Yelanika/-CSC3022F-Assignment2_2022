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
 
    int row = 0;
    int col = 0;
    unsigned char ** mImage = nullptr;
    std::vector<unsigned char **> imageSequence;
 
    //getting the dimensions of the image we are reading in
    void FrameSequence::getImageDimensions(std::string pgmFile) {
 
        std::cout << "filename: " << pgmFile << std::endl;
 
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
 
            mImage = new unsigned char*[col];
            for (int i =0; i < col; ++i) {
                    
                mImage[i] = new unsigned char[row];
                for (int j =0; j < row; ++j ) {
                    in.read((char*)&mImage[i][j],1);
                }
            }
        }
 
        in.close();
    }

    void FrameSequence::tracjectory(std::vector<int> x, std::vector<int> y, int width, int height, std::string operation, std::string name) {
 
        for (int d = 0; d < x.size()-1; d++ ) {

          //  std::cout << "d here" << std::endl;
            int x1 = x[d];
            int x2 = x[d+1];
           // std::cout << "x here" << std::endl;
            int y1 = y[d];
            int y2 = y[d+1];
            std::cout << d << std::endl;


            float g = ((float)(y2-y1))/((float)(x2-x1));
            //std::cout << "x1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2 << " g: " << g << std::endl;
            int count = 0;
            int op = 0;
    
            if (operation.compare("none") == false) {
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
            int slope = 0;

            if (std::fabs(g) < 1.0) {

                if (x2 < x1)
                    slope = -1;
                else
                    slope = 1;
                
                for (int x =x1; x < x2; x = x + slope) {
                    ystart = ystart + g; 
                    switch (op) {
                        case 1: { 
                            FrameSequence::none(x, std::round(ystart), width, height);
                            count++;
                            break;
                        }
                        case 2: {
                            FrameSequence::invert(x, std::round(y1), width, height);
                            count++;
                            break;
                        }
                    }
                }


            }
            else {
                if (y2 < y1) 
                    slope = -1;
                else    
                    slope = 1;
                for (int y=y1; y < y2; y = y +(slope)) {
                    x1+=(1/g);
                    switch (op) {
                        case 1: { 
                            FrameSequence::none(std::round(x1), y, width, height);
                            count++;
                            break;
                        }
                        case 2: {
                            FrameSequence::invert(std::round(x1), y, width, height);
                            count++;
                            break;
                        }
                    };
                }
            }
        }

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
 
    void FrameSequence::none(int x, int y, int width, int height) {
 
        unsigned char ** tracP = nullptr;
 
        int xCount = x;
        int yCount = y;
        tracP = new unsigned char*[width];
        for (int i = 0; i < width; ++i) {
            xCount++;
            tracP[i] = new unsigned char[height];
            for (int j =0; j < height; ++j ) {
                yCount++;
                tracP[i][j] = mImage[xCount][yCount];                              
            }
        }
 
        imageSequence.push_back(tracP);
    }
 
    void FrameSequence::invert(int x, int y, int width, int height) {
        
        unsigned char ** tracP = nullptr;
 
        int xCount = x;
        int yCount = y;
        tracP = new unsigned char*[width];
        for (int i = 0; i < width; ++i) {
            xCount++;
            tracP[i] = new unsigned char[height];
            for (int j =0; j < height; ++j ) {
                yCount++;
                int p = 255;
                int pixel = 255 - (int)(mImage[xCount][yCount]);
                int * ptr = nullptr;
                ptr = &pixel;

                unsigned char * chptr = (unsigned char *)ptr;
 
                tracP[i][j] = *chptr;                              
            }
        }
 
        imageSequence.push_back(tracP);
    }
 
    void FrameSequence::reversePrintImage(int width, int height, std::string name) {
 
        std::fstream out;  
        int fnew =0;
        for (int f = imageSequence.size()-1; f >=0; f--) {
 
            std::string fnum = std::to_string(fnew);
            std::string filename = name + fnum + ".pgm";
            out.open(filename, std::ios::out | std::ios::binary);
            out << "P5" << std::endl;
            out << "#The output file of the in file" << std::endl;
            out << width << " " << height << std::endl;
            out << "255" << std::endl;
            
            
            for (int i = 0; i < width; ++i) {
                for (int j =0; j < height; ++j ) {
 
                    unsigned char * ptr = nullptr;
                    ptr = &imageSequence[f][i][j];
                    out.write((char *)ptr,1);              
                }
            }
 
            out.close();
            fnew++;
        };
 
    }    
 
    void FrameSequence::printImage(int width, int height, std::string name) {
       
        std::fstream out;  
       // std::string strCount = std::to_string(count);
 
        for (int f =0; f < imageSequence.size(); f++) {
 
            std::string fnum = std::to_string(f);
            std::string filename = name + fnum + ".pgm";
            out.open(filename, std::ios::out | std::ios::binary);
            out << "P5" << std::endl;
            out << "#The output file of the in file" << std::endl;
            out << width << " " << height << std::endl;
            out << "255" << std::endl;
            
            
            for (int i = 0; i < width; ++i) {
                for (int j =0; j < height; ++j ) {
 
                    unsigned char * ptr = nullptr;
                    ptr = &imageSequence[f][i][j];
                    out.write((char *)ptr,1);              
                }
            }
 
            out.close();
        }
    }
 
    FrameSequence::~FrameSequence() {
        for (int i = 0; i < col; ++i) {
            delete [] mImage[i];
        }
        delete [] mImage;
 
        int isSize = imageSequence.size();
        for (int h = 0; h < isSize; ++h) {
            delete [] imageSequence[h];
        delete [] imageSquence;       
    }
    
}
