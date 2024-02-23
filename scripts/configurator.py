import io
import os
import string


class Configurator():
    """Создаёт в папке dir файлы с адаптерами интерфейсов, описанные в interfaces"""

    def __init__(self, interfaces: list, dir: string) -> None:
        self._interfaces = interfaces
        self._dir = dir
        self._file_list = list()

    def configure(self) -> list:
        """Производит конфигурацию файлов"""
        if not os.path.isdir(self._dir):
            os.mkdir(self._dir)

        for interface in self._interfaces:
            self._handle_interface(interface)

        return self._file_list

    def _handle_interface(self, interface: dict):
        methods = list(interface['methods'])
        if not len(methods):
            print("No methods")
            return

        className = interface['class']
        filename = f"Adapter{className}.h"

        file = io.open(self._dir + '/' + filename, "w")
        if not file:
            print(f"Failed open {filename} in {self._dir}")
            return

        line = f"""#pragma once\n\n#include \"Objects/{className}.h\"
#include \"Objects/UObject.h\"
#include \"IoC.h\"
                    \n"""

        namespaces = interface.get('namespaces')
        if namespaces:
            for namespace in namespaces:
                line += "namespace " + namespace + " {\n\n"
        file.write(line)

        line = f"class Adapter{className} : public {className}\n"
        file.write(line)

        line = '{\n\tUObject obj;\n\tIoC ioc;\npublic:\n'

        file.write(line)

        for method in methods:
            line = self._handle_method(className, method, namespaces)
            file.write(line)

        line = "};\n\n"
        if namespaces:
            for i in range(len(namespaces)):
                line += "}\n"

        file.write(line)

        file.close()
        self._file_list.append(filename)

    def _handle_method(self, className: str, method: dict, namespaces: list) -> str:
        returnType = method['return']
        methodName = method['name']
        line = f"\tvirtual {returnType} {methodName}("
        types = list()
        names = list()
        if method.get('args'):
            for arg in method['args']:
                type = arg[0]
                types.append(type)
                name = arg[1]
                names.append(name)
                line += f"{type} {name}, "

            line = line[:-2]

        line += ") override\n\t{\n\t\t"

        if returnType == 'void':
            ioc = "ioc.Resolve<ICommand, "
        else:
            ioc = f"return *ioc.Resolve<{returnType}, "

        ioc += "UObject, "

        for type in types:
            ioc += f"{type}, "

        ioc = ioc[:-2] + ">(\""

        for namespace in namespaces:
            ioc += f"{namespace}."

        ioc += f"{className}.{methodName}\", obj, "

        for name in names:
            ioc += f"{name}, "

        ioc = ioc[:-2]
        if returnType == 'void':
            ioc += ")->Execute("

        ioc += ");\n\t"
        line += ioc + "}\n"
        return line
