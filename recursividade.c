#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Pessoa
{
   char           nome[50];
   int            idade;
   int            numf;  // Número de filhos
   struct Pessoa *filhos;
};
typedef struct Pessoa Pessoa;
struct Pessoa *buscaPessoa(struct Pessoa *pessoaAsc, char nomeProcurado[], int nivel, int imprimeNivel);

int main()
{
   int n;

   scanf("%d", &n);
   Pessoa antecessor;

   for (int i = 0; i < n; i++)
   {
      char dir[50];
      char nome[50];
      int  idade;
      scanf("%s %d %s", nome, &idade, dir);
      if (i == 0)
      {
         strcpy(antecessor.nome, nome);
         antecessor.idade  = idade;
         antecessor.numf   = 0;
         antecessor.filhos = malloc(1 * sizeof(antecessor.filhos));
      }
      else
      {
         Pessoa *ascendenteDireto = buscaPessoa(&antecessor, dir, 1, 0);
         ascendenteDireto->numf++;
         ascendenteDireto->filhos = realloc(ascendenteDireto->filhos, ascendenteDireto->numf * sizeof(Pessoa));
         ascendenteDireto->filhos[ascendenteDireto->numf - 1].idade = idade;
         ascendenteDireto->filhos[ascendenteDireto->numf - 1].numf  = 0;
         strcpy(ascendenteDireto->filhos[ascendenteDireto->numf - 1].nome, nome);
      }
   }

   int m;

   scanf("%d", &m);

   for (int i = 0; i < m; i++)
   {
      char desc[50];
      char asc[50];
      scanf("%s %s", desc, asc);
      Pessoa *ascendente = buscaPessoa(&antecessor, asc, 1, 0);
      buscaPessoa(ascendente, desc, 0, 1);
   }

   free(antecessor.filhos);
   return(0);
}

struct Pessoa *buscaPessoa(struct Pessoa *pessoaAsc, char nomeProcurado[], int nivel, int imprimeNivel)
{
   if (strcmp(nomeProcurado, pessoaAsc->nome) == 0)
   {
      if (imprimeNivel)
      {
         printf("%d\n", nivel);
      }
      return(pessoaAsc);
   }
   nivel++;
   for (int i = 0; i < pessoaAsc->numf; i++)
   {
      struct Pessoa *pessoaRetornada = buscaPessoa(&pessoaAsc->filhos[i], nomeProcurado, nivel, imprimeNivel);
      if (pessoaRetornada != NULL)
      {
         return(pessoaRetornada);
      }
   }
   return(NULL);
}
