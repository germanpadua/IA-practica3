# Práctica 3 de *Inteligencia Artificial*, curso 2021/2022

## Realización de la práctica
El guión (disponible en [PRADO](https://pradogrado2122.ugr.es/)) contiene toda la información sobre en qué consiste la práctica3. Leelo con atención.
También tienes a tu disposición un tutorial con los primeros pasos a realizar.


### Instalación local

En el guión y el tutorial tienes las instrucciones. 
El software usa la librería [SFML](https://www.sfml-dev.org/index.php), por lo que debes instalarla según tu versión de linux:
- Ubuntu/Debian: `sudo apt install libsfml-dev`
- Arch: `sudo pacman -S sfml`
- Fedora/CentOS/Suse: `sudo dnf -y install SFML-devel` o `sudo yum -y install SFML-devel`

Si ninguna de estas opciones te funciona, también hay otras [opciones de instalación](https://www.sfml-dev.org/tutorials/2.5/start-linux.php)

Cuando realices cualquier modificación en el código, debes recompilar, así que usa `make`.


### Instalación en máquina virtual
Si no tienes linux de forma nativa en tu ordenador, puedes crear una máquina virtual en tu ordenador (por ejemplo, usando VirtualBox), e instalar linux en ella. A partir de ahí, puedes trabajar dentro de ella como si tuvieras linux instalado de forma nativa.


### Desarrollo remoto con Gitpod
Si prefieres no instalar nada localmente, puedes usar [Gitpod](https://gitpod.io). Este es un servicio que no depende de los profesores de la asignatura y que no podemos garantizar que funcione perfectamente. Para ello, haz click en el siguiente botón (después de modificarlo para que apunte a tu repositorio y no al de la asignatura) y sigue las instrucciones.

<!-- IMPORTANTE: Debes cambiar en el siguiente enlace TUSUARIO por tu nombre de usuario en github!  -->
[![Abrir con Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/TUSUARIO/practica3)

Una vez que el servidor remoto esté creado (la primera vez tardará un rato en configurarlo todo, las siguientes veces, debería ser más inmediato), verás un IDE completamente funcional en el navegador; puedes seguir usándolo, o usar VScode localmente si lo tienes instalado(aunque conectado al servidor Gitpod remoto). También, se te debería de haber abierto una nueva ventana en el navegador que te mostrará la interfaz gráfica del programa.

Si no se abre la ventana, copia la url del navegador y anteponle `6080-`. 
Por ejemplo, si la URL del IDE es `https://USUARIO-REPO-zzzzz.ws-eu34.gitpod.io` abriríamos en una nueva pestaña `https://6080-USUARIO-REPO-zzzzz.ws-eu34.gitpod.io`.


Si trabajas con Gitpod, ¡no olvides hacer commit de todos tus cambios para que se vayan guardando en tu repositorio!
