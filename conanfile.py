from conan import ConanFile
from conan.tools.cmake import *
from conan.tools.files import *
import os


class FtRecipe(ConanFile):
    name = "ft"
    package_type = "application"

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    exports_sources = "CMakeLists.txt", "src/*", "include/*", "unit_tests/*"

    def requirements(self):
        self.requires("cli11/2.4.1")
        self.test_requires("gtest/1.14.0")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cm = CMake(self)
        cm.configure()
        cm.build()

        if not self.conf.get("tools.build:skip_test", default=False):
            test_folder = os.path.join("unit_tests")
            self.run(os.path.join(test_folder, "test_ft --gtest_output='xml'"), ignore_errors=True)
    
    def package(self):
        copy(self, pattern="ft", src=self.build_folder, dst=self.package_folder, keep_path=False)