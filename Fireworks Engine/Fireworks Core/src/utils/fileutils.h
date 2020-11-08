#pragma once

#include <string>
#include <iostream>

namespace fireworks { namespace utils {

    /// A utility class to load various types of files
    class FileUtils
    {
    public:
        /// Reads the contents of the file and converts into stream of bytes
        /// 
        /// @param filepath The path of the file to read the data from
        static std::string read_file(const char* filepath)
        {
            FILE* file = fopen(filepath, "r");
            if (file == NULL)
            {
                // Log this!
                std::cerr << "ERROR::FILE::Cannot read the file - Please check the file path or permissions " << '\n';
                return 0;
            }
            fseek(file, 0, SEEK_END);
            unsigned long length = ftell(file);
            char* data  = new char[length + 1];
            memset(data, 0, length + 1);
            fseek(file, 0, SEEK_SET);
            fread(data, 1, length, file);
            fclose(file);

            std::string result(data);
            delete[] data;
            return result;
        }
    };
} }
