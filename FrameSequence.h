/**
 * Yelanika Gunasekara
 * GNSSEN002
 * FrameSequence.h
 * This is the header file for the FrameSequence class.
 * **/

#ifndef _FrameSequence_h
#define _FrameSequence_h
#include <string>
#include <vector>

namespace GNSSEN002 {
    class FrameSequence {

           int row;
           int col;
           unsigned char ** mImage;
           std::vector<unsigned char **> imageSequence;
            int height;
        public: 
            FrameSequence();    //default constructor
            //FrameSequence(int row, int col, unsigned char **mImage, std::vector<unsigned char **> imageSequence, int height);
            ~FrameSequence();   //destructor 
            bool getImageDimensions(std::string pgmFile);

            void tracjectory(std::vector<int> x, std::vector<int> y, int width, int height, std::string operation, std::string name);
            void invert(int x, int y, int width, int height);            
            void none(int x, int y, int width, int height);
            void reversePrintImage(int width, int height, std::string name);
            void printImage(int width, int height, std::string name);

    };
}

#endif