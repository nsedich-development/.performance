emscripten-installation
============

[Release Link]https://s3.amazonaws.com/mozilla-games/emscripten/releases/emsdk-portable-64bit.zip
[Download and install]https://kripken.github.io/emscripten-site/docs/getting_started/downloads.html
[Tutorial]https://kripken.github.io/emscripten-site/docs/getting_started/Tutorial.html#tutorial

~~~
# Fetch the latest registry of available tools.
./emsdk update
~~~

~~~
# Download and install the latest SDK tools.
./emsdk install latest
~~~

~~~
# Make the "latest" SDK "active" for the current user. (writes ~/.emscripten file)
./emsdk activate latest
~~~

~~~
# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh
~~~

**Note On Windows, run emsdk instead of ./emsdk, and emsdk_env.bat instead of source ./emsdk_env.sh.
**Note If you change the location of the SDK (e.g. take it to another computer on an USB), re-run the ./emsdk activate latest and source ./emsdk_env.sh commands.

**Useful Links**

[Getting started with WASM]https://tutorialzine.com/2017/06/getting-started-with-web-assembly

[OpenGL WASM]https://stackoverflow.com/questions/45121115/webassembly-opengl-single-context-many-output-to-canvas

[WASM arrays]https://github.com/DanRuta/wasm-arrays

[Web Workers]https://github.com/ChrisZieba/holdem
