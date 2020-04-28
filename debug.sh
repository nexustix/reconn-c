premake5 gmake2
make

if [ $# -gt 0 ]; then
  ./bin/Debug/reconn $@
else
  #rlwrap -S ">" ./bin/Debug/reconn $@
  ./bin/Debug/reconn $@
fi