import os
import string
import io


class Searcher():
    """Ищет рекурсивно файлы в директории rootDir, которые содержат классы, обозначенные словом label"""

    def __init__(self, rootDir: string, label: string) -> None:
        self._root = rootDir
        self._label = label
        self._class_list = list()

    def search(self) -> list:
        """Производит процедуру поиска"""
        self._class_list.clear()
        self._find_file(self._root)
        return self._class_list

    def _find_file(self, rootDir: string):
        """Ищет файлы в директории"""
        print("Looking label for in " + rootDir)
        for dir in os.listdir(rootDir):
            abs_path = os.path.join(rootDir, dir)
            if os.path.isdir(abs_path):
                self._find_file(abs_path)
            else:
                self._looking_for_label(abs_path)

    def _looking_for_label(self, fileName: string):
        """Ищет пометку, что из класса нужно сделать адаптер"""
        with io.open(fileName, encoding='utf-8') as file:
            for line in file:
                if self._label in line:
                    toPush = self._make_dict(file)
                    if (type(toPush) != type(None)):
                        print(f"Founded interface {toPush['class']}")
                        self._class_list.append(toPush)

    def _find_namespace(self, file: io.TextIOWrapper) -> list:
        file.seek(0)
        namespaces = list()
        try:
            for line in file:
                words = line.split()
                for i in range(len(words)):
                    if words[i] == self._label:
                        raise Exception
                    if words[i] == 'namespace':
                        if len(words) > i + 1:
                            namespaces.append(words[i+1])
                            break
        except:
            pass

        return namespaces

    def _find_methods(self, file: io.TextIOWrapper) -> list:
        methods = list()
        for line in file:
            line = line.replace('\n', '')
            if line.endswith(('};', '} ;')):  # последняя строка класса
                break
            if line.find('public:') != -1:
                continue

            openBrace = line.find('(')
            closeBrace = line.find(')')
            if openBrace == -1 or closeBrace == -1:
                continue
            if line.find('virtual') == -1:  # ключевое слово
                continue
            # чисто виртуальный метод
            if not line.endswith(('=0;', '= 0;', '=0 ;', '= 0 ;')):
                continue

            words = line.split()
            if len(words) < 3:      # 1. virtual 2. возвращаемое значение 3. имя метода
                continue

            method = dict()
            method['return'] = words[1]
            method['name'] = words[2].split('(')[0]
            args = line[openBrace+1:closeBrace]

            if args:
                args = args.split(',')
                method['args'] = list()
                for arg in args:
                    pair = tuple(arg.split(' '))
                    method['args'].append(pair)

            methods.append(method)

        return methods

    def _make_dict(self, file: io.TextIOWrapper) -> dict:
        """Создаёт словарь с методами класса"""
        nDict = dict()

        namespaces = self._find_namespace(file)
        if namespaces:
            nDict['namespaces'] = namespaces

        line = file.readline().split()
        try:
            i = line.index('class')
            if len(line) < (i + 2):
                return
        except ValueError:
            pass

        nDict['class'] = line[i+1]

        line = file.readline()
        if line.split()[0] != '{':
            return

        nDict['methods'] = self._find_methods(file)

        return nDict
