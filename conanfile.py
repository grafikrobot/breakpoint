from conan import ConanFile, tools
import os

required_conan_version = ">=1.53.0"


class Package(ConanFile):
    name = "debugging"
    homepage = "https://github.com/grafikrobot/debugging"
    description = "Utility functions to interact and introspect with a debugger running your program."
    topics = ("debugging", "debug")
    license = "MIT"
    url = "https://github.com/grafikrobot/debugging"
    barbarian = {
        "description": {
            "format": "asciidoc",
            "file": "README.adoc"
        }
    }
    exports = "README.adoc"
    source_subfolder = "source_subfolder"

    def source(self):
        tools.files.get(
            self,
            **self.conan_data["sources"][self.version],
            strip_root=True, destination=self.source_subfolder)

    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    tool_requires = ("b2/[>=4.7.0]@")
    python_requires = ("b2-conan/[>=1.0.0]@bfgroup/b2-conan")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        if self.options.shared:
            del self.options.fPIC

    def validate(self):
        if self.info.settings.compiler.cppstd:
            tools.build.check_min_cppstd(self, 11)

    def build(self):
        b2 = self.python_requires["b2-conan"].module.B2(self)
        sources = os.path.join(self.source_folder, self.source_subfolder)
        with tools.files.chdir(self, sources):
            b2.build(['-d+2'])

    def package(self):
        self.copy(
            pattern="LICENSE.txt", dst="licenses",
            src=self.source_subfolder)
        for pattern in ["*.h", "*.hpp", "*.hxx"]:
            self.copy(
                pattern=pattern, dst="include",
                src=os.path.join(self.source_subfolder, "include"))
        for pattern in ["*.lib", "*.so", "*.dylib", "*.a"]:
            self.copy(pattern=pattern, dst="lib", keep_path=False)
        for pattern in ["*.dll", "*.exe"]:
            self.copy(pattern=pattern, dst="bin", keep_path=False)
