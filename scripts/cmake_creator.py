import os
import io


class CmakeCreator():
    """Создаёт CMakeLists.txt с библиотекой с переданным списком файлов"""

    def __init__(self) -> None:
        pass

    def create(self, files: list, dir: str) -> bool:
        """"Создаёт cmake list с файлами files в папке dir"""
        if not os.path.isdir(dir):
            os.mkdir(dir)

        cmake = io.open(dir + '/' + 'CMakeLists.txt', "w")
        if not cmake:
            print(f"Failed create CMakeLists.txt in {dir}")
            return False

        line = "set(SOURCES\n\t"
        for file in files:
            line += f"{file}\n\t"

        cmake.write(line[:-1])

        line = """)\nadd_library(adapters SHARED ${SOURCES})
set_target_properties(adapters PROPERTIES LINKER_LANGUAGE CXX)"""
        cmake.write(line)
        cmake.close()
        return True
