
#include <fstream>
#include "gtest/gtest.h"

#include "../src/ft/file_thing.h"
#include "test_fixtures.h"

namespace
{
    // Create tests
    TEST_F(FileTestHarness, CreateFileWithText)
    {
        std::string text = "Hello, world!";
        int code = createFileWithText(testFilePath, text);

        // Check file exists and no error code
        ASSERT_TRUE(fs::exists(testFilePath));
        ASSERT_EQ(code, true);

        // Read the file and check if the content matches
        std::ifstream file(testFilePath);
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        ASSERT_EQ(content, text);
    }

    TEST_F(FileTestHarness, CreateFileWithoutText)
    {
        int code = createFileWithText(testFilePath);

        // Check file exists and no error code
        ASSERT_TRUE(fs::exists(testFilePath));
        ASSERT_EQ(code, true);

        // Check if file is empty
        std::ifstream file(testFilePath);
        ASSERT_TRUE(file.peek() == std::ifstream::traits_type::eof());
        file.close();
    }

    TEST_F(FileTestHarness, CreateFileWithoutDirs)
    {
        std::string invalidDirectoryPath = "invalid_directory";
        std::string invalidDestinationPath = invalidDirectoryPath + "/test_destination_file.txt";

        // Expect error message because directory does not exist
        int code = createFileWithText(invalidDestinationPath, "Hello, world!");
        ASSERT_EQ(code, false);
        ASSERT_FALSE(fs::exists(invalidDestinationPath));
    }

    // Copy tests
    TEST_F(CopyTestHarness, CopyFileSuccess)
    {
        ASSERT_EQ(copyFile(testSourceFilePath, testDestinationFilePath), true);

        // Check if destination file exists
        ASSERT_TRUE(fs::exists(testDestinationFilePath));

        // Check if destination file content matches source file content
        std::ifstream sourceFile(testSourceFilePath);
        std::ifstream destinationFile(testDestinationFilePath);
        ASSERT_EQ((std::istreambuf_iterator<char>(sourceFile)), (std::istreambuf_iterator<char>(destinationFile)));
        sourceFile.close();
        destinationFile.close();
    }

    TEST_F(CopyTestHarness, CopyNonExistentFile)
    {
        std::string nonExistentFilePath = "non_existent_file.txt";
        ASSERT_EQ(copyFile(nonExistentFilePath, testDestinationFilePath), false);

        // Check if destination file does not exist
        ASSERT_FALSE(fs::exists(testDestinationFilePath));
    }

    TEST_F(CopyTestHarness, CopyToInvalidDirectory)
    {
        std::string invalidDirectoryPath = "invalid_directory";
        std::string invalidDestinationPath = invalidDirectoryPath + "/test_destination_file.txt";
        ASSERT_EQ(copyFile(testSourceFilePath, invalidDestinationPath), false);

        // Check if destination file does not exist
        ASSERT_FALSE(fs::exists(invalidDestinationPath));
    }

    // Combine files tests
    TEST_F(CombineFileHarness, CombineFilesSuccess)
    {
        ASSERT_EQ(combineFiles(sourcePath1, sourcePath2, destinationPath), true);

        // Check if destination file exists
        ASSERT_TRUE(fs::exists(destinationPath));

        // Check if destination file content matches the combination of source file contents
        std::ifstream destinationFile(destinationPath);
        std::string combinedContent;
        combinedContent += "Contents of file 1";
        combinedContent += "Contents of file 2";
        std::string destinationContent((std::istreambuf_iterator<char>(destinationFile)), (std::istreambuf_iterator<char>()));
        destinationFile.close();
        ASSERT_EQ(destinationContent, combinedContent);
    }

    TEST_F(CombineFileHarness, CombineFilesNonExistentSource)
    {
        std::string nonExistentFilePath = "non_existent_file.txt";
        ASSERT_EQ(combineFiles(nonExistentFilePath, sourcePath2, destinationPath), false);
        ASSERT_FALSE(fs::exists(destinationPath));
    }

    TEST_F(CombineFileHarness, CombineFilesInvalidDestinationDir)
    {
        std::string invalidDirectoryPath = "invalid_directory2";
        std::string invalidDestinationPath = invalidDirectoryPath + "/combined_file.txt";
        ASSERT_EQ(combineFiles(sourcePath1, sourcePath2, invalidDestinationPath), false);
        ASSERT_FALSE(fs::exists(invalidDestinationPath));
    }

    // Delete tests
    TEST_F(DeleteFileHarness, DeleteExistingFile)
    {
        ASSERT_EQ(deleteFile(filePath), true);

        ASSERT_FALSE(fs::exists(filePath));
    }

    TEST_F(DeleteFileHarness, DeleteNonExistentFile)
    {
        std::string nonExistentFilePath = "non_existent_file.txt";
        ASSERT_EQ(deleteFile(nonExistentFilePath), false);
    }

}