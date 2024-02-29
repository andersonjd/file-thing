#ifndef FILE_THING_H_
#define FILE_THING_H_

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * Create a new file, optionally containing provided text
 * 
 * @param file The path the file to create
 * @param text Optional text to insert into new file
 * 
 * @return True if command was successful
*/
bool createFileWithText(const fs::path& file = "", const std::string& text = "");

/**
 * Copy a file
 * 
 * @param sourcePath The path to the source file
 * @param destinationPath The path of the copy
 * 
 * @return True if command was successful
*/
bool copyFile(const fs::path& sourcePath, const fs::path& destinationPath);

/**
 * Combine two files into a third new file
 * 
 * @param sourcePath1 The path the first file
 * @param sourcePath2 The path the second file
 * @param destinationPath The path to the combined file
 * 
 * @return True if command was successful
*/
bool combineFiles(const fs::path& sourcePath1, const fs::path& sourcePath2, const fs::path& destinationPath);

/**
 * Delete a file
 * 
 * @param filePath The path to the file to delete
 * 
 * @return True if command was successful
*/
bool deleteFile(const fs::path& filePath);

#endif // FILE_THING_H_