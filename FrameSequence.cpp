#include "FrameSequence.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include <fstream>
#include <sstream>

namespace GNSSEN002 {

    FrameSequence( row , col,mImage) : row(row), col(col), mImage(mImage) {};

    //getting the dimensions of the image we are reading in
    void FrameSequence::getImageDimensions(std::string pgmFile) {

        std::cout << "filename: " << pgmFile << std::endl;

        std::ifstream in(pgmFile, std::ios::in | std::ios::binary);
        std::string checkDigitStr = "";
        bool Dimensions = false;
        row = 0;
        col = 0;
        std::string p5;
        std::vector<std::string> comments;
        std::string twofivefive;
        mImage = nullptr;
        std::string temp;     
        

        int count = 0;

        //Error checking: if the file does not exist or fails to open
        if (!in) {
            std::cerr << "File failed to open." << std::endl;
        }
        //if the file opens/exists, the data in the file is extracted
        else {

            std::getline(in, p5);
            std::getline(in, temp);
            std::getline(in, checkDigitStr);
                    
                  
            std::istringstream iss(checkDigitStr);
            iss >> col >> std::ws >> row;
            std::cout << "row: " << row << " col: " << col << std::endl;

            //std::getline(in, twofivefive);
            in >> twofivefive >> std::ws;

            mImage = new unsigned char*[col];
            for (int i =0; i < col; ++i) {
                    
                mImage[i] = new unsigned char[row];
                for (int j =0; j < row; ++j ) {
                    in.read((char*)&mImage[i][j],1);
                }
            }
            std::cout << "row: " << row << " col: " << col << std::endl;
        }

        in.close();

//sloan = 1, large = 0;  
        std::cout << row << "r : c" << col << std::endl;
        std::fstream out;
        out.open("pgmOut.pgm", std::ios::out | std::ios::binary);

        out << "P5" << std::endl;
        out << "#The output file of the in file" << std::endl;
        out << col << " " << row << std::endl;
        out << "255" << std::endl;

        for (int i = 0; i< col; ++i) {
            for (int j =0; j < row; ++j) {
                out.write((char*)&mImage[i][j],1);
            }
        }

         out.close();


        std::cout << "It works to this point" << std::endl;
    }

    void invert() {

        std::fstream out;
        out.open();

        for (int i = 0; i < col; ++i) {
            for (int j =0; j < row; ++j ) {
                
            }
        }
    }
    
}