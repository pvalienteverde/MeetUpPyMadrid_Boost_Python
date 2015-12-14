from distutils.core import setup
from distutils.extension import Extension
from distutils.ccompiler import new_compiler
import glob
import fnmatch
import os
import pkg_resources
import tempfile
import shutil
import subprocess

#https://pythonhosted.org/setuptools/setuptools.html

def BuscadorArchivos(carpeta_raiz,tipo):
    matches = []
    for root, dirnames, filenames in os.walk(carpeta_raiz):
        for filename in fnmatch.filter(filenames, tipo):
            matches.append(os.path.join(root, filename))            
    return matches   


os.chdir(os.path.dirname(os.path.realpath(__file__)))

c = new_compiler()
compilador_por_defecto=['gcc']
c.compiler_so=compilador_por_defecto
c.compiler=compilador_por_defecto
c.compiler_cxx=compilador_por_defecto

# Includes
includes_brutos=subprocess.Popen(['python3-config','--includes'], stdout=subprocess.PIPE).communicate()[0]
PYTHON_INCLUDES=includes_brutos.decode(encoding='UTF-8').replace('\n','').replace('-I','').split(' ')
CONVERTIBLES_INCLUDE=['convertidores']
UTILES_INCLUDE=['utiles']

INCLUDES_CONVERTIBLES_TODOS=CONVERTIBLES_INCLUDE.copy()
INCLUDES_CONVERTIBLES_TODOS.extend(PYTHON_INCLUDES)

INCLUDES_UTILES_TODOS=UTILES_INCLUDE.copy()
INCLUDES_UTILES_TODOS.extend(PYTHON_INCLUDES)

INCLUDES_WRAPPER_UTILES=['/usr/local/include']
INCLUDES_WRAPPER_UTILES.extend(CONVERTIBLES_INCLUDE)
INCLUDES_WRAPPER_UTILES.extend(UTILES_INCLUDE)
INCLUDES_WRAPPER_UTILES.extend(PYTHON_INCLUDES)

# Flags
todos_flags=subprocess.Popen(['python3-config','--cflags'], stdout=subprocess.PIPE).communicate()[0]
PYTHON_FLAGS=todos_flags.decode(encoding='UTF-8').replace('\n','').replace('  ',' ').split(' ')

FLAGS=['-c','-fmessage-length=0','-std=c++14','-fPIC']
FLAGS.extend(PYTHON_FLAGS)

c.compile(BuscadorArchivos('convertidores','*.cpp'),output_dir='bin',include_dirs=INCLUDES_CONVERTIBLES_TODOS,extra_preargs=FLAGS)

objetos_convertidores=BuscadorArchivos('bin/convertidores','*.o')
c.create_static_lib(objetos_convertidores, "convertidores", output_dir='lib', target_lang="c++")


c.compile(BuscadorArchivos('utiles','*.cpp'),output_dir='bin',include_dirs=INCLUDES_UTILES_TODOS,extra_preargs=FLAGS)

objetos_utiles=BuscadorArchivos('bin/utiles','*.o')
c.create_static_lib(objetos_utiles, "utiles", output_dir='lib', target_lang="c++")



modulo_wrapper_utiles = Extension('wrapper_utiles',
                    include_dirs=INCLUDES_WRAPPER_UTILES,
                    libraries=["convertidores","utiles", "boost_python3"],
                    library_dirs=['/usr/local/lib','lib'],
                    extra_compile_args=FLAGS,
                    #extra_objects=[],
                    sources=BuscadorArchivos('wrapper_utiles','*.cpp'))   

 
 
setup(name="wrapper_utiles",
       version='1.0',
       description='Ejemplo C++ Boost Python',
       author='Pedro Valiente Verde',
       author_email = "pvalienteverde@gmail.com",
       license = "MIT",
       url = "https://github.com/pvalienteverde/MeetUpPyMadrid_Boost_Python",
       ext_modules=[modulo_wrapper_utiles]
       )

