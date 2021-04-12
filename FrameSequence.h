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
        
        //private:
            //int row;
           // int col;
           // unsigned char ** mImage;
           /// std::vector<unsigned char **> imageSequence;
            //int width;
            //int height;
        public: 
         //   FrameSequence();
           // FrameSequence(int row, int col, int width, int height, unsigned char mImage, std::vector<unsigned char> imageSequence);
            ~FrameSequence();
           // int getWidth(int width);
            void getImageDimensions(std::string pgmFile);
            void tracjectory(std::vector<int> x, std::vector<int> y, int width, int height, std::string operation, std::string name);
            void invert(int x, int y, int width, int height);            
            void none(int x, int y, int width, int height);
            void reversePrintImage(int width, int height, std::string name);
            void printImage(int width, int height, std::string name);

    };
}

#endif