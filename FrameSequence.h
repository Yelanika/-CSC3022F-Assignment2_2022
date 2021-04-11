#ifndef _FrameSequence_h
#define _FrameSequence_h
#include <string>

namespace GNSSEN002 {
    class FrameSequence {

       // private:
            
        public: 
           // int row, col;
            //unsigned char ** mImage;

           // FrameSequence();
            //FrameSequence(const int row, const int col, unsigned char mImage);
            ~FrameSequence();
            void getImageDimensions(std::string pgmFile);
            void invert(int x, int y, int count, int width, int height, std::string name);
            void reverse(int x, int y, int count, int width, int height, std::string name);
            void revinvert(int x, int y, int count, int width, int height, std::string name);
            void none(int x, int y, int count, int width, int height, std::string name);
            void tracjectory(int x1, int y1, int x2, int y2, int width, int height, std::string operation, std::string name);
            void printImage(int width, int height, std::string name);
           
    };
}

#endif