mkdir -p ./build
cd ./build
cmake .. -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
cmake --build .
cd ..
./build/target/traqbot_event
