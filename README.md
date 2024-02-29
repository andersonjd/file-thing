# File Thing

File Thing is a command line utility for basic file manipulation tasks.  You can create a file (empty or with text), copy a file from one location to another, combine two files to create a third, or delete a file.

Manipulate files with ease!

Developed and tested on:
 - Ubuntu 22.04
 - gcc version 11.4.0 (c++ 17 std)
 - conan 2.1
 - cmake 3.22

 **NOTE:** The actions runners and Artifactory instance in use for this project are self-hosted on my personal workstation.  As such they are not available 24/7.  If a workflow is triggered while unavailable, the jobs will be stuck in the queue until they become available.

## Installation

A pre-built Debian package is available here: [Releases](https://github.com/andersonjd/file-thing/releases).

Download the deb and install:

```sh
$ sudo dpkg -i ft_0.3-1_amd64.deb
```

## Usage 

File Thing uses a subcommand style interface similar to git. The following commands are available:
- [Create](#create)  
- [Copy](#copy)  
- [Combine](#combine)  
- [Delete](#delete)  

**NOTE:**  File Thing will not create any directories, so if you want to create, copy, or combine files to a non-existant directory use `mkdir` to create the directory first.

### Create

Create a new file.

```sh
Create a file
Usage: ft create [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -f,--file TEXT REQUIRED     File name
  -t,--text TEXT              Optional text to be inserted into file
```

Examples:
```sh
$ ft create --file path/to/file.txt

```

```sh
$ ft create -f path/to/file.txt -t "Here is some text."
```

### Copy

Copy a file to another location.

```sh
$ ft copy --help
Copy a file from one location to another
Usage: ft copy [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -s,--source TEXT REQUIRED   Source file
  -d,--dest TEXT REQUIRED     Destination file
```

Example: 
```sh
$ ft copy -s original_file.txt -d copy.txt
```

### Combine

Combine two files into a third new file.

```sh
Combine two files into a third
Usage: ft combine [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -1,--file1 TEXT REQUIRED    Source file 1
  -2,--file2 TEXT REQUIRED    Source file 2
  -d,--dest TEXT REQUIRED     Destination
```
Example:
```sh
$ ft combine -1 file1.txt -2 file2.txt -d combined.txt
```

### Delete

Delete a file.

```sh
Delete a file
Usage: ft delete [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -f,--file TEXT REQUIRED     File to delete
```
Example:
```sh
$ ft delete -f delete_me.txt
```
## Repo structure

Overview of this repsoitory and its contents.

```
.
├── builder.sh                // Script for building ft binary
├── CMakeLists.txt            // CMake project definition
├── conanfile.py              // Conan ft recipe
├── LICENSE
├── package.sh                // Script to build deb package
├── README.md                   
├── src     
│   ├── cli                   // Code for handling cli related tasks 
│   │   ├── commands.cpp
│   │   └── commands.h
│   ├── ft                    // Code for actual ft functionaliy
│   │   ├── file_thing.cpp
│   │   └── file_thing.h
│   └── main.cpp              // ft main
├── test_package.sh           // Integration test script
└── unit_tests                // Unit test code
    ├── CMakeLists.txt
    ├── main.cpp              // Test main
    └── test_fixtures.h       // Helpers for unit tests
```

## Building

Building requires Conan, CMake, and a working C++ toolchain. To install all required dependencies install the following packages on an Ubunutu machine:

```sh
$ apt install -y build-essential cmake python3 python3-pip dh-make devscripts lintian
```

Then install Conan using pip and setup your system's default profile:

```sh
$ pip install conan
$ conan profile detect -f
```
For more detailed instructions see the official conan docs [here](https://docs.conan.io/2/installation.html).

### Building ft for local development

Once all dependencies are installed, building ft locally is as easy as running the `builder.sh` script:

```sh
$ ./builder.sh
```
This will trigger the conan based build, and the resultant binary should be located in `build/Release`.

### Building and running ft unit tests

The `builder.sh` convenience script also provides a way to do this:

```sh
$ ./builder.sh unit_test
```
This will compile the unit test binary and run it, displaying the test results in the terminal.

### Creating the deb package

To create the deb package locally, first use `builder.sh` to build the binary.

```sh
$ ./builder.sh
```

Then run the `package.sh` script to generate the deb. This script requires an environment variable `VERSION` set to run.

```sh
$ ./builder.sh
$ VERSION='0.3' ./package.sh
```
This will create the deb package in your project root folder:
```sh
$ ls -la *.deb
-rw-r--r-- 1 janderson janderson 142226 Feb 28 16:56 ft_0.3-1_amd64.deb
```

### Running integration tests

With the ft package installed in your system, run the `test_package.sh` script:

```sh
$ ./test_package.sh 
Running installation checks...
Passed!

Running create test...
Passed!

Running copy test...
Passed!

Running combine test...
Passed!

Running delete test...
Passed!
```

## Contributing

To contribute to the development of File Thing, create a branch in this repo with your changes.  Then open a PR targeting `main`.  This will trigger a Github action workflow that runs the unit test and integration test to ensure everythign is still working.

You can see the results of a previous workflow here: [PR #4](https://github.com/andersonjd/file-thing/actions/runs/8089394857?pr=4)

Once your PR is merged, a workflow will run that creates the release Debian package and a draft release will be created for project maintainers to approve.

