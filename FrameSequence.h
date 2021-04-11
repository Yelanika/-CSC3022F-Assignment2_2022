#ifndef _FrameSequence_h
#define _FrameSequence_h
#include <string>

namespace GNSSEN002 {
    class FrameSequence {

       // private:
            int row, col;
            unsigned char ** mImage;

        public:
            FrameSequence();
            FrameSequence(const int row, const int col, unsigned char mImage);
            ~FrameSequence();
            void getImageDimensions(std::string pgmFile);
            void invert();
            void reverse();
            void revinvert();
            
    };
}

#endif