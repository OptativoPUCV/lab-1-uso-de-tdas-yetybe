#!/bin/bash
exec 3>&1 4>&2
trap 'exec 2>&4 1>&3' 0 1 2 3

# Limpiar el archivo log
> log

# Verificar cambios en exercises.c
CHANGED=$(git diff --ignore-space-at-eol -b -w --ignore-blank-lines exercises.c)

# Si hay cambios o no existe a.out, recompilar
if [ -n "$CHANGED" ] || [ ! -f "a.out" ]; then
  echo "$(date): " >> log
  git diff --stat --ignore-space-at-eol -b -w --ignore-blank-lines exercises.c >> log

  # Compilación
  echo "Compiling with: gcc test.c -Wall -Werror -o a.out" >&3
  if gcc test.c -Wall -Werror -o a.out 2>>log ; then
      echo  " tests: " $(($(./a.out | grep -c 'OK')))\|$(($(./a.out | grep -c 'FAILED'))) >> log
      ./a.out | tail -n1 >> log
      git rev-parse --short HEAD >> log
      git add exercises.c log &> /dev/null
      git commit -m 'new try' &> /dev/null
  else
      echo "Compilation with errors :c" >&3
      echo "Compilation failed" >> log
      gcc test.c -Wall -Werror -o a.out 2>&3
      git rev-parse --short HEAD >> log
      git add exercises.c log &> /dev/null
      git commit -m 'new try' &> /dev/null
      exit 1
  fi
fi

# Ejecutar pruebas
if ./a.out &> /dev/null ; then
  echo "Executing: ./a.out" >&3
  ./a.out >&3

  echo "Quiere actualizar su avance en el servidor? (s|n): " >&3
  read response

  if [ "$response" == "s" ]; then
    git pull >&3
    git push >&3
  fi
else
  echo "Errors in execution =O" >&3
  gcc -g test.c -o a.out >&3
  gdb -silent -ex='set disable-randomization off' -ex='set confirm off' -ex='run' -ex=quit a.out >&3
fi