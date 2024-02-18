class FileTestHarness : public ::testing::Test
{
protected:
    void SetUp() override
    {
        testDirectoryPath = "test_output";
        fs::create_directories(testDirectoryPath);

        testFilePath = testDirectoryPath + "/test_file.txt";
    }

    void TearDown() override
    {
        fs::remove_all(testDirectoryPath);
    }

    std::string testDirectoryPath;
    std::string testFilePath;
};

class CopyTestHarness : public ::testing::Test
{
protected:
    void SetUp() override
    {
        testSourceDirectory = "test_source_directory";
        testDestinationDirectory = "test_destination_directory";
        testSourceFilePath = testSourceDirectory + "/test_source_file.txt";
        testDestinationFilePath = testDestinationDirectory + "/test_destination_file.txt";

        fs::create_directories(testSourceDirectory);
        fs::create_directories(testDestinationDirectory);
        std::ofstream sourceFile(testSourceFilePath);
        sourceFile << "Test file content";
        sourceFile.close();
    }

    void TearDown() override
    {
        fs::remove_all(testSourceDirectory);
        fs::remove_all(testDestinationDirectory);
    }

    std::string testSourceDirectory;
    std::string testDestinationDirectory;
    std::string testSourceFilePath;
    std::string testDestinationFilePath;
};

class CombineFileHarness : public ::testing::Test
{
protected:
    void SetUp() override
    {
        sourceDirectory = "source_directory";
        destinationDirectory = "destination_directory";
        fs::create_directories(sourceDirectory);
        fs::create_directories(destinationDirectory);

        sourcePath1 = sourceDirectory + "/source_file1.txt";
        sourcePath2 = sourceDirectory + "/source_file2.txt";
        destinationPath = destinationDirectory + "/combined_file.txt";

        std::ofstream sourceFile1(sourcePath1);
        sourceFile1 << "Contents of file 1";
        sourceFile1.close();

        std::ofstream sourceFile2(sourcePath2);
        sourceFile2 << "Contents of file 2";
        sourceFile2.close();
    }

    void TearDown() override
    {
        fs::remove_all(sourceDirectory);
        fs::remove_all(destinationDirectory);
    }

    std::string sourceDirectory;
    std::string destinationDirectory;
    std::string sourcePath1;
    std::string sourcePath2;
    std::string destinationPath;
};

class DeleteFileHarness : public ::testing::Test
{
protected:
    void SetUp() override
    {
        testDirectoryPath = "test_directory";
        fs::create_directories(testDirectoryPath);

        filePath = testDirectoryPath + "/test_file.txt";
        std::ofstream testFile(filePath);
        testFile.close();
    }

    void TearDown() override
    {
        //fs::remove_all(testDirectoryPath);
    }

    std::string filePath;
    std::string testDirectoryPath;
};
