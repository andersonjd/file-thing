#include "file_thing.h"

#include <fstream>

int createFileWithText(const fs::path &filePath, const std::string &text)
{
    try
    {
        // Attempt to open file
        std::ofstream file(filePath);

        if (!file.is_open())
        {
            std::cerr << "Failed to create file: " << filePath << std::endl;
            std::cerr << "Make sure the target directories exist and you have permission to write to the location." << std::endl;
            return 1;
        }

        // Write to file if there is text
        if (!text.empty())
        {
            file << text;
        }

        file.close();

        std::cout << "File created successfully: " << filePath << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error copying file: " << e.what() << std::endl;
        return 1;
    }
}

int copyFile(const fs::path &sourcePath, const fs::path &destinationPath)
{
    try
    {
        // Check if source file exists
        if (!fs::exists(sourcePath))
        {
            std::cerr << "Source file does not exist: " << sourcePath << std::endl;
            return 1;
        }

        // Copy the file
        fs::copy(sourcePath, destinationPath, fs::copy_options::overwrite_existing);

        std::cout << "File copied successfully from " << sourcePath << " to " << destinationPath << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error copying file: " << e.what() << std::endl;
        return 1;
    }
}

int combineFiles(const fs::path &sourcePath1, const fs::path &sourcePath2, const fs::path &destinationPath)
{
    try
    {
        // Open source files
        std::ifstream sourceFile1(sourcePath1);
        if (!sourceFile1.is_open())
        {
            std::cerr << "Failed to open source file 1: " << sourcePath1 << std::endl;
            return 1;
        }

        std::ifstream sourceFile2(sourcePath2);
        if (!sourceFile2.is_open())
        {
            std::cerr << "Failed to open source file 2: " << sourcePath2 << std::endl;
            return 1;
        }

        // Open destination file
        std::ofstream destinationFile(destinationPath);
        if (!destinationFile.is_open())
        {
            std::cerr << "Failed to create destination file: " << destinationPath << std::endl;
            std::cerr << "Make sure directory exists." << std::endl;
            return 1;
        }

        // Combine contents of source files into destination file
        destinationFile << sourceFile1.rdbuf() << sourceFile2.rdbuf();

        sourceFile1.close();
        sourceFile2.close();
        destinationFile.close();

        std::cout << "Files combined successfully." << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error combining files: " << e.what() << std::endl;
        return 1;
    }
}

int deleteFile(const fs::path &filePath)
{
    try
    {
        // Check if file exists
        if (!fs::exists(filePath))
        {
            std::cerr << "File does not exist: " << filePath << std::endl;
            return 1;
        }

        // Delete the file
        if (!fs::remove(filePath))
        {
            std::cerr << "Error deleting file: " << std::endl;
        }
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error deleting file: " << e.what() << std::endl;
        return 1;
    }
}