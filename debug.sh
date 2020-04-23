premake5 gmake2
make

#

if [ $# -gt 0 ]; then
  ./bin/Debug/cstarter $@
else
  rlwrap -S ">" ./bin/Debug/cstarter $@
fi