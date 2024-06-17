cd ../../build

g++ \
  -fdiagnostics-color=always \
  -Wall \
  -g3 \
  -o \
  ../bin/app.out \
  *.o \
  -lSDL2 \
  -lSDL2_image \

echo "Compilation complete!"