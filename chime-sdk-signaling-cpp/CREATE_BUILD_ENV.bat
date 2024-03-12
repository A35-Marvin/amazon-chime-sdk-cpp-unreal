rmdir /s /q build
mkdir build
cd build
cmake -DCMAKE_SYSTEM_VERSION=10.0.19041.0 -DCMAKE_GENERATOR_TOOLSET=v142 -DCMAKE_BUILD_TYPE=Release --fresh -DLWS_WITH_SSL=1 -A x64 ..
pause