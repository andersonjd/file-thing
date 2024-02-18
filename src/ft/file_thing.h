#ifndef FILE_THING_H_
#define FILE_THING_H_

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int createFileWithText(const fs::path& file = "", const std::string& text = "");
int copyFile(const fs::path& sourcePath, const fs::path& destinationPath);
int combineFiles(const fs::path& sourcePath1, const fs::path& sourcePath2, const fs::path& destinationPath);
int deleteFile(const fs::path& filePath);

#endif // FILE_THING_H_