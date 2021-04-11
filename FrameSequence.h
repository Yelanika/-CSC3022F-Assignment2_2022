#ifndef _FrameSequence_h
#define _FrameSequence_h
#include <string>

namespace GNSSEN002 {
    class FrameSequence {
            
        public: 
            ~FrameSequence();
            void getImageDimensions(std::string pgmFile);
            void invert(int x, int y, int width, int height);
            void reverse(int width, int height, std::string name);
            void none(int x, int y, int width, int height);
            void tracjectory(int x1, int y1, int x2, int y2, int width, int height, std::string operation, std::string name);
            void printImage(int width, int height, std::string name);

    };
}

#endif