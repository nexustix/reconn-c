rm -r build/
bs --debug -o test.ninja test.bs
ninja -f ./test.ninja
build/demo/exe/demo.exe