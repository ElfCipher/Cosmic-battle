from searcher import Searcher
from configurator import Configurator
from cmake_creator import CmakeCreator
import sys

print("Start " + sys.argv[0])

source_path = sys.argv[1]
build_path = sys.argv[2]

ser = Searcher(source_path, '[[Adaptable]]')
interfaces = ser.search()

if not len(interfaces):
    exit(0)

config = Configurator(interfaces, build_path)
files_name = config.configure()

if not len(files_name):
    print("Failed configure adapters")
    exit(1)

creator = CmakeCreator()

if not creator.create(files_name, build_path):
    print("Failed create CMakeLists.txt")
    exit(1)