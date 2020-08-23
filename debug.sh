rm -r build/
bs -o test.ninja test.bs
ninja -f ./test.ninja
build/demo/exe/demo.exe