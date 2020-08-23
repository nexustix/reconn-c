rm -r build/
bs -o test.ninja test.bs
ninja -f ./test.ninja
valgrind --leak-check=full --track-origins=yes build/demo/exe/demo.exe