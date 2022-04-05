// chg-text-file-encoding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>

int main()
{
    // Take input
    std::string inFileName, outFileName;
    std::cout << "Input file name (default is Jira.csv): ";
    std::getline(std::cin, inFileName);
    // std::cin >> inFileName;
    if (inFileName.empty()) {
        inFileName = "Jira.csv";
    }
    outFileName = "output-" + inFileName;

    //std::ifstream fileIn(inFileName);
    std::ifstream fileIn(inFileName, std::ios::in | std::ios::binary);  // Binary mode to overcome 0x1A problem

    std::string line;
    if (fileIn.is_open()) {
        std::ofstream fileOut(outFileName);
        fileOut.imbue(std::locale(fileOut.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
        // Start the output text file with byte order mark (BOM)
        unsigned char bom[] = { 0xEF,0xBB,0xBF };
        fileOut.write((char*)bom, sizeof(bom));
        // Write to output file
        std::string content((std::istreambuf_iterator<char>(fileIn)), (std::istreambuf_iterator<char>()));
        fileOut << content;
        /*
        while (std::getline(fileIn, line))
        {
            // fileOut << line << '\n';
            fileOut << line << std::endl;
        }
        */
        fileIn.close();
        fileOut.close();
        std::cout << "Conversion completed, press any key to exit ...";
    }
    else {
        std::cout << "Unable to open file, please check and try again.";
    }

    std::getline(std::cin, inFileName);
    return 0;
}
