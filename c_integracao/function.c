// https://www.lua.org/pil/25.2.html

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
 

/* function declaration */
float * f (lua_State* L);
void error (lua_State *L, const char *fmt, ...);

int main(int argc, const char* argv[]){
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  //entrada do nome do arquivo
  char arquivo[10];
  printf("Digite o nome do arquivo lua: \n");
  scanf("%s", &arquivo);

  // carrega o arquivo e executa suas ações
  luaL_dofile(L, arquivo);

  float *valor = f(L);
  int t = (int)( sizeof(valor) / sizeof(valor[0]) );
  for (int i = 0; i<t; i++){
    printf("resultado %d: %f\n",i, valor[i]);
  }

  lua_close(L);
  return 0;
}

/* call a function `calculo' defined in Lua */
float * f (lua_State* L) {
  double z;

  //entrada do nome da funcao 
  char funcao[10];
  printf("Digite o nome da função: \n");
  scanf("%s", &funcao);

  /* push functions and arguments */
  lua_getglobal(L, funcao);  /* function to be called */

  //numero de argumentos 
  int argumentos = 0;
  int a = 0;
  printf("Digite o número de argumentos: \n");
  scanf("%d", &argumentos);
  for (int i=0;i<argumentos;i++){
    int argumento = 0;
    printf("Digite o %dº argumento: ", i);
    scanf("%d", &argumento);

    lua_pushnumber(L, argumento);
    a = i;
  }
  //número de resultados
   int resultados = 0;
   printf("digite o numero de reusultados: \n");
   scanf("%d", &resultados);
  /* do the call (2 arguments, 1 result) */
  if (lua_pcall(L, a+1, resultados, 0) != 0)
    error(L, "error running function `calculo': %s",
              lua_tostring(L, -1));

  /* retrieve result */
  if (!lua_isnumber(L, -1))
    error(L, "function `calculo' must return a number");
  double result;
  int i =0;

  float *v= malloc (sizeof (float) * resultados-1);
  while (i<resultados) {  
    result = lua_tonumber(L, -1);
    v[i] = result;
    lua_pop(L, 1);
    i++;
  }
  return v;
}

// https://www.lua.org/pil/24.1.html#first-ex
void error (lua_State *L, const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
  lua_close(L);
  exit(EXIT_FAILURE);
}