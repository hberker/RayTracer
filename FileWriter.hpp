#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include <fstream>
#include "Color.hpp"

class FileWriter
{
    private:
        const char* FILENAME;
        const int WIDTH;
        const int HEIGHT;

        std::ofstream img;

        void initFile();
    public:
        FileWriter(const char*, int, int);
        FileWriter();

        void writeOutPixel(Color);
    
};

FileWriter::FileWriter(const char* filename, int w, int h) : FILENAME(filename), WIDTH(w), HEIGHT(h) 
{
    initFile();
}


FileWriter::FileWriter() : FILENAME("NAME_NOT_DECLARED.ppm"), WIDTH(800), HEIGHT(800)
{
    initFile();
}

void FileWriter::initFile()
{
    img = std::ofstream(FILENAME);
    img << "P3"<< std::endl;
    img << WIDTH << " " << HEIGHT << std::endl;
    img << "255" << std::endl; 
}
void FileWriter::writeOutPixel(Color c)
{
    img << c.getR() << " " << c.getG() << " " << c.getB() << std::endl;
}

#endif