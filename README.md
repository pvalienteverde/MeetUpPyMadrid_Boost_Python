# MEETUP PyMadrid BoostPython

Contiene el material necesario para la charla sobre boost.python para la comunidad de Python Madrid

La presentacion consta de 3 partes fundamentales:

 * Lo primero, quitarnos la verguenza. Nada mejor que con el clasico HolaMundo
 * Nos metemos de lleno en la extension de funciones, con un ejemplo de mas a menos.
 * Por ultimo, la envoltura  de una clase externa

** NOTA: La presentacion se ha desarrollado bajo Fedora 22/23 y utilizando Python3.4. **

# Instalacion para sistemas LINUX (FEDORA)

Se ha usado las distribuciones facilitadas por el sistema

 * **[Boost.Python](http://boost.org)** Es una parte del paquete de boost. Como ademas, en los ejemplos se utiliza otros paquetes de Boost se recomienda la instalacion completa, Recodar, tambien los paquetes dev y cabeceras. Ademas, como se utiliza Python3.X nos tenemos que asegurar de instalar boost-python3
 * **Python** Utilizamos para todo el paquete **Python3.X**. Si alguien utiliza Python2.X el cambio deberia ser trivial
 * El compilar que mas nos guste. Para esta charla, se utilizara **gcc**
 * Tengo la construmbre de desarrollar en el entorno de programacion Eclipse, por lo que he facilitado los proyectos. Pero no se requiere para este proposito puesto que se ha dejado un makefile para los ejemplos de funciones y setup.py para las clases
* **Paquetes de python**: [pandas](http://pandas.pydata.org), [numpy](http://www.numpy.org), [bokeh](http://bokeh.pydata.org/en/latest) y [ipython](http://ipython.org/)

Es decir:
```bash
sudo dnf install python3-devel python3-ipython gcc-c++ boost boost-python* python3-pandas python3-pip
sudo pip3 install ipython
sudo pip3 install pandas 
sudo pip3 install numpy 
sudo pip3 install bokeh  
```

# Desarrollo

**Lo primero de todo es compilar los ejemplos para luego lanzar el cuarderno ipython guardado con el desarrollo de la charla:**
```bash
git clone https://github.com/pvalienteverde/MeetUpPyMadrid_Boost_Python MeetUpMadrid
# Compilamos los ejemplos de wrappers de funciones
cd MeetUpMadrid/WrapperFunciones
make all
# Compilamos los ejemplos de wrappers de clases externas
cd ../WrapperClases
python3 setup.py build
```
## Hay dos formas de seguir despues de  la compilacion
### 1: Ejecutar el cuaderno de ipython

```bash
# Carpeta raiz MeetUpMadrid
cd Python
ipython3 notebook 
```

### 2: A traves de las diapositivas
```bash
# Carpeta raiz MeetUpMadrid
cd Python
ipython3 nbconvert MeetUpMadrid_Diciembre_2015_Boost_Python.ipynb --to slides --post serve  --config slides_config.py --template slides_template.tpl 
```

# Presentacion
La presentacion está guardada en la siguiente direccion: http://pvalienteverde.github.io/MeetUpPyMadrid_Boost_Python/
