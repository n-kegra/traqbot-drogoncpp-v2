mkdir -p ./build
cd ./build
cmake ..
cmake --build .
cd ..
./build/target/traqbot_event
