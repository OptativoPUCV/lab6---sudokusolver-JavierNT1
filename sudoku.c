#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int verificarFilasColumnas(Node* n){
   int i, j;
   for(i = 0; i < 9; i++){
      int a[9] = {0};
      int b[9] = {0};
      for(j = 0; j < 9; j++){
         if(n->sudo[i][j] != 0){
            if(a[n->sudo[i][j] - 1] == 0){
               a[n->sudo[i][j] - 1] = 1;
            }
            else{
               return 0;
            }
         }
         if(n->sudo[j][i] != 0){
            if(b[n->sudo[j][i] - 1] == 0){
               b[n->sudo[j][i] - 1] = 1;
            }
            else{
               return 0;
            }
         }
      }
   }
   return 1;
}

int subMatriz(Node* n){
   int k, p;
   for(k = 0; k < 9; k++){
      int a[9] = {0};
      for(p = 0; p < 9; p++){
         int i = 3*(k/3) + (p/3);
         int j = 3*(k%3) + (p%3);
         if(n->sudo[i][j] != 0){
            if(a[(n->sudo[i][j] - 1)] == 0){
               a[(n->sudo[i][j]) - 1] = 1; 
            }
            else
               return 0;
         }
      }
   }
   return 1;
}

int is_valid(Node* n){
   if(verificarFilasColumnas(n) == 1)
      if (subMatriz(n) == 1)
         return 1;
      
      
   
   return 0;
}

List* get_adj_nodes(Node* n){
   List* list=createList();
   for(int i = 0; i < 9 ; i++){
      for(int j = 0; j < 9; j++){
         if(n->sudo[i][j] == 0){
            for(int k = 1; k < 10; k++){
               Node* new = createNode();
               new = copy(n);
               new->sudo[i][j] = k;
               if(is_valid(new))
                  pushBack(list, new);
            }
          return list;  
         }
      }
   }
   return list;
}


int is_final(Node* n){
   for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
         if(n->sudo[i][j] == 0){
            return 0;
         }
      }
   }
   return 1;
}

void insert(List* lista, Stack* P){
   Node* aux = first(lista);
   while(aux != NULL){
      push(P, aux);
      aux = next(lista);
   }
}

Node* DFS(Node* initial, int* cont){
   Stack* pila = createStack();
   push(pila, initial);
   Node* aux = createNode();
   while(top(pila) != NULL){
      aux = top(pila);
      pop(pila);
      if(is_final(aux)) return aux;
      else{
         cont++;
         List* lista = get_adj_nodes(aux);
         insert(lista, pila);
      }
   }
   return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}
*/