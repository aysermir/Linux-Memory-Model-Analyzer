#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

typedef struct Node{
    char type[10];
    char name[1024];
    char size[1024];
    struct Node* next;
}Var_Node;

typedef struct RONode{
  char type[10];
  char name[1024];
  char size[1024];
  char scope[1024];
  struct RONode *next;
}RONode;


typedef struct HeapNode{
  char type[10];
  char name[1024];
  char size[1024];
  char scope[1024];
  struct HeapNode *next;
}HeapNode;

typedef struct func_node{
  char name[1024];
  int num_lines;
  struct func_node *next;
  struct Node *var;
  bool curr;
}Func_Node;

void delete_character(char * line, char c){
    int x; 
    int y;
    int len = strlen(line);
    for(x=0; x<len; x++){
      if(line[x] == c){
      for(y=x; y<len; y++){
        line[y] = line[y+1];
      }
      len--;
      x--;}
    }
}

bool checkPrintf(char *line){
  char *a = strstr(line, "printf");
  if(a!=NULL){
    return true;
  }
  return false;
}


bool check_star(char *line){
  char *a = strchr(line, '*');
  if(a==NULL){
    return false;
  }
  return true;
}


Var_Node *push_variable(Var_Node *head, char *type, char *name, char *size){

    Var_Node *node = NULL;
    node = (Var_Node*)calloc(1, sizeof(Var_Node));


    strcpy(node->name, name);
    strcpy(node->type, type);
    strcpy(node->size, size);
    node->next = NULL;

    Var_Node *ptr=head;
    if(head==NULL){
        return node;
    }
    while(ptr->next!=NULL){
        ptr = ptr->next;
    }
    ptr->next = node;
    return head;
}


Func_Node *push_function(Func_Node *head, char *name){
  Func_Node *node = NULL;
    node = (Func_Node*)calloc(1, sizeof(Func_Node));
    delete_character(name, '*');
    strcpy(node->name, name);
    node->num_lines = -1;
    node->next = NULL;
    node->curr = false;
    node->var=NULL;
    Func_Node *ptr=head;
    if(head==NULL){
        return node;
    }
    while(ptr->next!=NULL){
        ptr = ptr->next;
    }
    ptr->next = node;
    return head;




}


int is_empty(const char *s) {
  while (*s != '\0') {
    if (!isspace((unsigned char)*s))
      return 0;
    s++;
  }
  return 1;
}


char *removewhitespace(char *line)
{
  char *p;
  while(isspace((char)*line)){
    line++;
  }
  if(*line == 0){
    return line;
  }
  p = line -1 + strlen(line);
  while(p > line && isspace((char)*p)){
  p--;
  }
  p[1] = '\0';
  return line;
}


char *func_name(char *word){
  char *x = strtok(word, "(");
  return x;
}


bool check_parentheses(char *line){

  char *a = strchr(line, '(');
  char *b = strchr(line ,')');
  if(a==NULL && b == NULL){
    return false;
  }
  return true;

}

bool check_brackets(char* line){
  char *a = strchr(line, '[');
  char *b = strchr(line, ']');
  if(a==NULL && b==NULL){
    return false;
  }
  return true;
}

Var_Node *add_int_arr(Var_Node *head, char *line){
char copy[1024];
char len[20];
char size[20] = "\0";
for(int i = 0; i<strlen(line); i++){
  if(line[i]=='['){
    for(int y = i+1, z= 0; y<strlen(line); y++, z++){
      if(line[y]==']'){
        len[z] = '\0';
        break;
      }
      len[z] = line[y];
    }
  }
}
char *p = removewhitespace(len);
if(is_empty(p)){
  strcpy(copy, line);
  int num = 0;
  char *z = strtok(copy, ",");
  while(z!=NULL){
    z = strtok(NULL, ",");
    num++;
  }
  sprintf(size, "%d", num);

  strcat(size, "*sizeof(int)\0" );
}else{
  strcat(len, "*sizeof(int)\0");
  strcpy(size, len);
}
    char *a = strtok(line, " ");
  while(a!=NULL){
    if(strcmp(a, "int")!=0){
      a[strcspn(a, "[")] = 0;
      a = removewhitespace(a);
      head = push_variable(head, "int[]", a, size);
      return head;
    }

    a = strtok(NULL, ",");
  }
  return head;
}

Var_Node *add_float_arr(Var_Node *head, char *line){

char copy[1024];
char len[20];
char size[20];
for(int i = 0; i<strlen(line); i++){
  if(line[i]=='['){
    for(int y = i+1, z= 0; y<strlen(line); y++, z++){
      if(line[y]==']'){
        len[z] = '\0';
        break;
      }
      len[z] = line[y];
    }
  }
}
char *p = removewhitespace(len);
if(is_empty(p)){
  strcpy(copy, line);
  int num = 0;
  char *z = strtok(copy, ",");
  while(z!=NULL){
    z = strtok(NULL, ",");
    num++;
  }
  sprintf(size, "%d", num);
  strcat(size, "*sizeof(float)" );
}else{
  strcat(len, "*sizeof(float)");
  strcpy(size, len);
}
    char *a = strtok(line, " ");
  while(a!=NULL){
    if(strcmp(a, "float")!=0){
      a[strcspn(a, "[")] = 0;
      a = removewhitespace(a);
      head = push_variable(head, "float[]", a, size);
      return head;
    }

    a = strtok(NULL, ",");
  }
  return head;
}


Var_Node *add_char_arr(Var_Node *head, char *line){


char copy[1024];
char len[20];
char size[20];
for(int i = 0; i<strlen(line); i++){
  if(line[i]=='['){
    for(int y = i+1, z= 0; y<strlen(line); y++, z++){
      if(line[y]==']'){
        len[z] = '\0';
        break;
      }
      len[z] = line[y];
    }
  }
}
char *p = removewhitespace(len);
if(is_empty(p)){
  strcpy(copy, line);
  int num = 0;
  char *z = strtok(copy, ",");
  while(z!=NULL){
    z = strtok(NULL, ",");
    num++;
  }
  sprintf(size, "%d", num);
  strcat(size, "*sizeof(char)" );
}else{
  strcat(len, "*sizeof(char)");
  strcpy(size, len);
}
    char *a = strtok(line, " ");
  while(a!=NULL){
    if(strcmp(a, "char")!=0){
      a[strcspn(a, "[")] = 0;
      a = removewhitespace(a);
      head = push_variable(head, "char[]", a, size);
      return head;
    }

    a = strtok(NULL, ";");
  }
  return head;
}



Var_Node *add_int(Var_Node *head, char* line){
    if(check_brackets(line)){
      head = add_int_arr(head, line);
      return head;
    }else{
    line[strcspn(line, ";")] = 0;
    char *a = strtok(line, " ");

    while(a!=NULL){
    
    if(strcmp(a, "int")!=0){


      a[strcspn(a, "=")] = 0;
      a = removewhitespace(a);
      int size = sizeof(int);
      char s[1024];
      sprintf(s,"%d", size);
      head = push_variable(head, "int", a, s);
    }

    a = strtok(NULL, ",");
  }
  return head;
    }
}


Var_Node *add_char(Var_Node *head, char* line){
  if(check_brackets(line)){
      head = add_char_arr(head, line);
      return head;
    }else{
  line[strcspn(line, ";")] = 0;
  char *a = strtok(line, " ");
  while(a!=NULL){
    
    if(strcmp(a, "char")!=0){


      a[strcspn(a, "=")] = 0;
      a = removewhitespace(a);
      int size = sizeof(char);
      char s[1024];
      sprintf(s, "%d", size);
      head = push_variable(head, "char", a, s);
    }

    a = strtok(NULL, ",");
  }
  return head;
    }
}

Var_Node *add_float(Var_Node *head, char* line){
  if(check_brackets(line)){
      head = add_float_arr(head, line);
      return head;
    }
    line[strcspn(line, ";")] = 0;
  char line_copy[1024];
  strcpy(line_copy,line);
  char *a = strtok(line, " ");
  while(a!=NULL){
    
    if(strcmp(a, "float")!=0){


      a[strcspn(a, "=")] = 0;
      a = removewhitespace(a);
      int size = sizeof(float);
      char s[1024];
      sprintf(s, "%d", size);
      head = push_variable(head, "float", a, s);
    }

    a = strtok(NULL, ",");
  }
  return head;
}

Func_Node *add_function(Func_Node *head, char *line){
  char *a = strtok(line, " ");
  a = strtok(NULL, " ");
  a[strcspn(a, "(")] = 0;
  a = removewhitespace(a);
  head = push_function(head, a);
  return head;
}

void printGlobalVariables(Var_Node *head){
  printf("### static data ###\n");
  Var_Node *ptr = head;
  while(ptr!=NULL){
    printf("   %s   global   %s   %s\n", ptr->name, ptr->type, ptr->size);
    ptr = ptr->next;
  }
  printf("\n");

}

void printFunctionNames(Func_Node *head){
  Func_Node *ptr = head;
  int num = 0;
  while(ptr!=NULL){
    num ++;
    ptr = ptr->next;
  }
  printf("  - Total number of functions: %d\n", num);

  ptr = head;
  printf("   ");
  while(ptr!=NULL){
    printf(" %s", ptr->name);
    if(ptr->next!=NULL) printf(",");
    ptr = ptr->next;
    
  }
  printf("\n");

  }

void printNumFileLines(char *file){
  
FILE* f;
    f = fopen(file, "r");

    int lines = 0;
    char ch;
while(!feof(f))
{
  ch = fgetc(f);
  if(ch == '\n')
  {
    lines++;
  }
}
printf("  - Total number of lines in the file: %d\n", lines+1);
}


Func_Node *addFuncLines(Func_Node *head, int lines){
  Func_Node *ptr = head;
  if(ptr==NULL){
    return head;
  }
  while(ptr->next!=NULL){
    ptr=ptr->next;
  }
  ptr->num_lines = lines-1;
  return head;
}

void printFuncLines(Func_Node *head){

  Func_Node *ptr = head;
  printf("  - Total number of lines per functions:\n");
  while(ptr!=NULL){
    printf("    %s: %d\n", ptr->name, ptr->num_lines);
    ptr=ptr->next;
  }

}

void printProgramName(char *name){
  printf(">>> Memory Model Layout <<<\n\n");
  printf("***  exec // text ***\n");
  printf("   %s\n\n", name);

}

Var_Node *add_string_literal_to_stack(Var_Node *head, char *line){
  printf("YES\n");
  char line_copy[1024];
  strcpy(line_copy,line);
  line[strcspn(line,";")]=0;
  char *a = strtok(line, " ");
  while(a!=NULL){
    if(strcmp(a, "char*")!=0 && strcmp(a, "char")!=0){
      char name[1024];
      int i = 0;
      for(i = 0;i<strlen(a); i++){
        if(a[i]=='='){
          break;
        }
        name[i] = a[i];
      }
      name[i] = '\0';
      char *n = name;
      n = removewhitespace(n);  
      char value[1024];

      int z;
      for(int ind=0;ind<strlen(a);ind++){
        if(a[ind]=='"'){
          z = ind;
          break;
        }
      }
      for(int y = z+1, h = 0; y<strlen(a);y++, h++){
        if(a[y]=='"'){
          value[h] = '\0';
          break;
        }
        value[h] = a[y];
      }
      int a = strlen(value);
      char size[1024];
      sprintf(size, "%d", a);
      delete_character(name, '*');
      char *nam = removewhitespace(name);
      head = push_variable(head, "char*", nam, "8");
    }

    a = strtok(NULL, ",");
  }
  return head;
}




Var_Node *add_float_pointer(Var_Node *head, char *line){
    char line_copy[1024];
  strcpy(line_copy,line);
  line[strcspn(line, ";")] = 0;
  char *a = strtok(line, " ");
  while(a!=NULL){
    if(strcmp(a, "float*")!=0 && strcmp("float", a)!=0){


      a[strcspn(a, "=")] = 0;
      a = removewhitespace(a);
      delete_character(a, '*');
      head = push_variable(head, "float*", a, "8");
    }

    a = strtok(NULL, ",");
  }
  return head;
}

Var_Node *add_int_pointer(Var_Node *head, char *line){
    char line_copy[1024];
  strcpy(line_copy,line);
  line[strcspn(line, ";")] = 0;
  char *a = strtok(line, " ");
  while(a!=NULL){
    
    if(strcmp(a, "int*")!=0 && strcmp(a, "int")!=0){


      a[strcspn(a, "=")] = 0;
      
      delete_character(a, '*');
      a = removewhitespace(a);
      int size = sizeof(int *);
      char s[1024];
      sprintf(s, "%d", size);
      head = push_variable(head, "int*", a, s);
    }

    a = strtok(NULL, ",");
  }
  return head;
  
}

void printUnusedSpace(){
  printf("####################\n");
  printf("### unused space ###\n");
  printf("####################\n\n");
}







Var_Node *varFunc(Var_Node *head, char *name, char *type, char *size){
    Var_Node *node = NULL;
  node = (Var_Node*)calloc(1, sizeof(Var_Node));
  strcpy(node->name, name);
  strcpy(node->type, type);
  strcpy(node->size, size);
  node->next = NULL;

  Var_Node *ptr = head;
  if(ptr == NULL){
    
    return node;
  }
  while(ptr->next!=NULL){
    ptr = ptr->next;
  }

  ptr->next = node;
  return head;

  
}

Func_Node* var_to_func(Func_Node *head, char *name, char *type, char* size){
    Func_Node *ptr = head;
  while(ptr!=NULL){
      Var_Node *v = ptr->var;
      if(ptr->curr){
        ptr->var = varFunc(v, name, type, size);
    }
    ptr = ptr->next;
  }
  ptr = head;
  while(ptr!=NULL){
    ptr = ptr->next;
  }
  return head;
}

Var_Node *add_int_arr_to_func(Var_Node *head, char *line){

char copy[1024];
char len[20];
char size[20] = "\0";

for(int i = 0; i<strlen(line); i++){
  if(line[i]=='['){
    for(int y = i+1, z= 0; y<strlen(line); y++, z++){
      if(line[y]==']'){
        len[z] = '\0';
        break;
      }
      len[z] = line[y];
    }
  }
}
char *p = removewhitespace(len);
if(is_empty(p)){
  strcpy(copy, line);
  int num = 0;
  char *z = strtok(copy, ",");
  while(z!=NULL){
    z = strtok(NULL, ",");
    num++;
  }

  sprintf(size, "%d", num);

  strcat(size, "*sizeof(int)\0" );
}else{
  strcat(len, "*sizeof(int)\0");
  strcpy(size, len);
}
    char *a = strtok(line, " ");
  while(a!=NULL){
    if(strcmp(a, "int")!=0){


      a[strcspn(a, "[")] = 0;
      a = removewhitespace(a);
      head = push_variable(head, "int[]", a, size);
      return head;
    }

    a = strtok(NULL, ",");
  }
  return head;
}

Func_Node *add_int_to_func(Func_Node *head, char* line){
  if(check_brackets(line)){
      Func_Node *ptr = head;
      while(ptr->next!=NULL){
        ptr = ptr->next;
      }
      Var_Node *var = ptr->var;
      if(var==NULL){
        ptr->var = add_int_arr_to_func(var, line);
      return head;
      }
      while(var->next!=NULL){
        var = var->next;
      }
      var = add_int_arr_to_func(var, line);
      return head;
    }else{
  char line_copy[1024];
  line[strcspn(line, ";")] = 0;
  strcpy(line_copy,line);
  char *a = strtok(line_copy, " ");
  while(a!=NULL){
    if(strcmp(a, "int")!=0){


      a[strcspn(a, "=")] = 0;
      int size = sizeof(int);
      char s[1024];
      sprintf(s, "%d", size);
      a = removewhitespace(a);
      head = var_to_func(head, a, "int", s);
    }

    a = strtok(NULL, ",");
  }
  return head;
    }
}

Func_Node *add_float_to_func(Func_Node *head, char* line){
    
    if(check_brackets(line)){
      
      Func_Node *ptr = head;
      while(ptr->next!=NULL){
        ptr = ptr->next;
      }
      Var_Node *var = ptr->var;
      if(var==NULL){
        ptr->var = add_float_arr(var, line);
      return head;
      }
      while(var->next!=NULL){
        var = var->next;
      }  
      var = add_float_arr(var, line);
      return head;
    }else{
      
  char line_copy[1024];
  line[strcspn(line, ";")] = 0;
  strcpy(line_copy,line);
  char *a = strtok(line_copy, " ");
  while(a!=NULL){
    if(strcmp(a, "float")!=0){


      a[strcspn(a, "=")] = 0;
      int size = sizeof(float);
      char s[1024];
      sprintf(s, "%d", size);
      a = removewhitespace(a);
      head = var_to_func(head, a, "float", s);
    }

    a = strtok(NULL, ",");
  }
  return head;
    }
}


void printStack(Func_Node *head){
    printf("### stack ###\n");
  Func_Node *ptr = head;
  while(ptr!=NULL){
    Var_Node *v = ptr->var;
    while(v!=NULL){
      printf("   %s   %s   %s   %s\n", v->name, ptr->name, v->type, v->size);
      v = v->next;
    }


    ptr = ptr->next;
  }
  printf("\n");


}




typedef struct line{
  char line[1024];
  struct line *next;
}Line;


Line *push_line(Line *head, char *line){

  Line *new = (Line*)calloc(1, sizeof(Line));
  strcpy(new->line, line);
  new->next = NULL;
  if(head==NULL){
    return new;
  }
  Line *ptr = head;
  while(ptr->next!=NULL){
    ptr=ptr->next;
  }
  ptr->next = new;
  return head;


}


Func_Node *add_char_to_func(Func_Node *head, char* line){
      if(check_brackets(line)){
      Func_Node *ptr = head;
      while(ptr->next!=NULL){
        ptr = ptr->next;
      }
      Var_Node *var = ptr->var;
      if(var==NULL){
        ptr->var = add_char_arr(var, line);
      return head; 
      }
      while(var->next!=NULL){
        var = var->next;
      }
      var = add_char_arr(var, line);
      return head;
    }else{
  char line_copy[1024];
  line[strcspn(line, ";")] = 0;
  strcpy(line_copy,line);
  char *a = strtok(line_copy, " ");
  while(a!=NULL){
    if(strcmp(a, "char")!=0){


      a[strcspn(a, "=")] = 0;
      int size = sizeof(char);
      char s[1024];
      sprintf(s, "%d", size);
      a = removewhitespace(a);
      head = var_to_func(head, a, "char", s);
    }
    a = strtok(NULL, ",");
  }
  return head;
    }
}

Func_Node *add_int_pointer_to_func(Func_Node *head, char* line){
  char line_copy[1024];
  line[strcspn(line, ";")] = 0;
  strcpy(line_copy,line);
  char *a = strtok(line_copy, " ");
  while(a!=NULL){
    if(strcmp(a, "int")!=0 && strcmp("int*", a)!=0){


      a[strcspn(a, "=")] = 0;
      int size = sizeof(int*);
      char s[1024];
      sprintf(s, "%d", size);
      delete_character(a, '*');
      a = removewhitespace(a);
      head = var_to_func(head, a, "int*", s);
    }
    a = strtok(NULL, ",");
  }
  return head;
}

Func_Node *add_int_pointer_to_func_heap(Func_Node *head, char* line){
  char line_copy[1024];
  line[strcspn(line, ";")] = 0;
  strcpy(line_copy,line);
  char *a = strtok(line_copy, " ");
  while(a!=NULL){
    if(strcmp(a, "int")!=0 && strcmp("int*", a)!=0){
 

      a[strcspn(a, "=")] = 0;
      int size = sizeof(int*);
      char s[1024];
      sprintf(s, "%d", size);
      delete_character(a, '*');
      a = removewhitespace(a);
      head = var_to_func(head, a, "int*", s);
      return head;
    }
    a = strtok(NULL, ",");
  }
  return head;
}

Func_Node *add_float_pointer_to_func(Func_Node *head, char* line){
  char line_copy[1024];
    line[strcspn(line, ";")] = 0;
  strcpy(line_copy,line);
  char *a = strtok(line_copy, " ");
  while(a!=NULL){
    if(strcmp(a, "float")!=0 && strcmp("float*", a)!=0){


      a[strcspn(a, "=")] = 0;
      int size = sizeof(float*);
      char s[1024];
      sprintf(s, "%d", size);
      delete_character(a, '*');
      a = removewhitespace(a);
      head = var_to_func(head, a, "float*", s);
    }
    a = strtok(NULL, ",");
  }
  return head;
}

Func_Node *add_char_pointer_to_func(Func_Node *head, char* line){
  char line_copy[1024];
  line[strcspn(line, ";")] = 0;
  strcpy(line_copy,line);
  char *a = strtok(line_copy, " ");
  while(a!=NULL){
    if(strcmp(a, "char")!=0 && strcmp("char*", a)!=0){


      a[strcspn(a, "=")] = 0;
      int size = sizeof(char*);
      char s[1024];
      sprintf(s, "%d", size);
      delete_character(a, '*');
      a = removewhitespace(a);
      head = var_to_func(head, a, "char*", s);
    }
    a = strtok(NULL, ",");
  }
  return head;
}

Func_Node *add_char_pointer_to_func_heap(Func_Node *head, char* line){
  char line_copy[1024];
  strcpy(line_copy,line);
  char *a = strtok(line_copy, " ");
  while(a!=NULL){
    if(strcmp(a, "char")!=0 && strcmp("char*", a)!=0){


      a[strcspn(a, "=")] = 0;
      int size = sizeof(char*);
      char s[1024];
      sprintf(s, "%d", size);
      delete_character(a, '*');
      a =removewhitespace(a);
      head = var_to_func(head, a, "char*", s);
      return head;
    }
    a = strtok(NULL, ";");
  }
  return head;
}


Func_Node *add_char_star_star_to_func(Func_Node *head, char* line){
  char line_copy[1024];
  strcpy(line_copy,line);
  char *a = strtok(line_copy, " ");
  while(a!=NULL){
    if(strcmp(a, "char**")!=0){


      a[strcspn(a, "=")] = 0;
      int size = sizeof(char**);
      char s[1024];
      sprintf(s, "%d", size);
      a = removewhitespace(a);
      head = var_to_func(head, a, "char**", s);
    }
    a = strtok(NULL, ";");
  }
  return head;
}



Func_Node *add_parameters(Func_Node *head, char *line){
  char line_copy[1024];
  Line *h = NULL;
  strcpy(line_copy, line);
  char *a = strchr(line, '(');
  a[strcspn(a, ")")] = 0;
  char copy[1024];
  int x=0;
  int i =1;
  for(i = 1,x=0; i<strlen(a);i++, x++){
    copy[x] = a[i];
  }
  copy[i-1]='\0';
  char *comm = strtok(copy, ",");


  while(comm!=NULL){
    comm = removewhitespace(comm);
  h = push_line(h, comm);
  comm = strtok(NULL, ",");
  }
  while(h!=NULL){
    char type[10];

    int i;
    for(i = 0; i<strlen(h->line);i++){
      if(h->line[i]==' '){
        break;
      }type[i] = h->line[i];
    }
    type[i] = '\0';

    if((strcmp("int",type)==0 && check_star(h->line))|| strcmp("int*", type)==0){
      head = add_int_pointer_to_func(head, h->line);
    }
    else if((strcmp("float",type)==0 && check_star(h->line))|| strcmp("float*", type)==0){
      head = add_float_pointer_to_func(head, h->line);
    }
    else if((strcmp("char",type)==0 && check_star(h->line))|| strcmp("char*", type)==0){
      head = add_char_pointer_to_func(head, h->line);
    }
    else if(strcmp("int", type)==0){
    head = add_int_to_func(head, h->line);
    }
    else if(strcmp("float", type)==0){
    head = add_float_to_func(head, h->line);
    }
    else if(strcmp("char", type)==0){
    head = add_char_to_func(head, h->line);
    }
    else if(strcmp("char**", type)==0){
      head = add_char_star_star_to_func(head, h->line);
    }
    h = h->next;
  }
  return head;
}



bool checkMalloc(char *line){
  char *a = strstr(line, "malloc");
  if(a==NULL){
    return false;
  }
  return true;
}


bool checkCalloc(char *line){
  char *a = strstr(line, "calloc");
  if(a==NULL){
    return false;
  }
  return true;
}



void printHeapData(HeapNode *head){
  printf("### heap ###\n");
  HeapNode *ptr=head;
  while(ptr!=NULL){
    printf("   %s   %s   %s   %s\n", ptr->name, ptr->scope, ptr->type, ptr->size);
    ptr = ptr->next;
  }
  printf("\n");
}




HeapNode *push_heap(HeapNode *head, char *type, char *name, char *size, char *scope){
  HeapNode *new = NULL;
  new = (HeapNode*)calloc(1, sizeof(HeapNode));
  strcpy(new->name, name);
  strcpy(new->type, type);
  strcpy(new->size, size);
  strcpy(new->scope, scope);
  new->next = NULL;
  if(head == NULL){
    return new;
  }
  HeapNode *ptr = head;
  while(ptr->next!=NULL){
    ptr = ptr->next;
  }
  ptr->next = new;
  return head;

}

char *remove_white_spaces(char *line){
	int x = 0;
  int y = 0;
	while (line[x]){
		if (line[x]!=' '){line[y++] = line[x];}
		x++;
	}
	line[y] = '\0';
	return line;
}


Func_Node *add_float_pointer_to_func_heap(Func_Node *head, char* line){
  char line_copy[1024];
    line[strcspn(line, ";")] = 0;
  strcpy(line_copy,line);
  char *a = strtok(line_copy, " ");
  while(a!=NULL){
    if(strcmp(a, "float")!=0 && strcmp("float*", a)!=0){


      a[strcspn(a, "=")] = 0;
      int size = sizeof(float*);
      char s[1024];
      sprintf(s, "%d", size);
      delete_character(a, '*');
      a = removewhitespace(a);
      head = var_to_func(head, a, "float*", s);
      return head;
    }
    a = strtok(NULL, ",");
  }
  return head;
}








HeapNode *push_calloc(HeapNode *head, char *line, bool in_function, Func_Node *func, Var_Node *var){
char NAME[1024];
  char type[1024];
  line[strcspn(line, ";")] = 0;

  char *a = strstr(line, "calloc");
  char *b = strstr(a, "(");

  int i;
  for(i = 1; i<strlen(b); i++){
    if(b[i]=='('){
      break;
    }
  }
  for(int x = i+1, j=0; i<strlen(b);x++,j++){
    if(b[x]==')'){
      type[j] = '\0';
      break;
    }
    type[j] = b[x];
  }
  


  for(int z = 1, p=0; z<strlen(b)-1;p++, z++){
    NAME[p] = b[z];
    NAME[p+1] = '\0';
  }

  char s[1024];
  strcpy(s, NAME);



  char copy[1024];
  strcpy(copy, line);
  
  copy[strcspn(copy, "=")] = 0;
    char *c = removewhitespace(copy);
    char *tok = strtok(c, " ");
    
    while(tok!=NULL){

      
      if(strcmp(tok, "int")!=0 && strcmp(tok, "int*")!=0 && strcmp(tok, "char")!=0 && strcmp(tok, "char*")!=0 && strcmp(tok, "float*")!=0 && strcmp(tok, "float")!=0){
      break;}
      tok = strtok(NULL, " ");
      
    }
    
  strcat(NAME, ")");
  delete_character(tok, '*');
      if(!in_function){
      delete_character(type, '*');
      char first[1024];
      char second[1024];
      int xx;
      for(xx = 0; xx<strlen(s);xx++){
        if(s[xx]==','){
          first[xx] = '\0';
          break;
        }
        first[xx] = s[xx];
      }
      for(int zz = xx+1, yy=0; zz<strlen(s);zz++, yy++){
        
        second[yy] = s[zz];
        second[yy+1] = '\0';
      }
      strcat(first, "*");
      char *sec = removewhitespace(second);
      strcat(first, sec);
      strcpy(s, first);

      
      head = push_heap(head, type, tok, s, "global");
      
      char line_copy[1024];
      strcpy(line_copy, line);
      char *i = strtok(line_copy, " ");
        if(strcmp("float", i)==0 || strcmp("float*",i)==0){
        int size = sizeof(float*);
        char s[1024];
        sprintf(s, "%d", size);
        delete_character(NAME, '*');
        var = push_variable(var, "float*", tok, s);
      }else if(strcmp("char", i)==0 || strcmp("char*",i)==0){
        int size = sizeof(char*);
        char s[1024];
        sprintf(s, "%d", size);
        delete_character(NAME, '*');
        var = push_variable(var, "char*", tok, s);
      }else if(strcmp("int", i)==0 || strcmp("int*",i)==0){
        int size = sizeof(int*);
        char s[1024];
        sprintf(s, "%d", size);
        delete_character(NAME, '*');
        var = push_variable(var, "int*", tok, s);
      }
      }else{
        Func_Node *ptr = func;
        while(ptr->next!=NULL){
          ptr = ptr->next;
        }
        head = push_heap(head, type, tok, s, ptr->name);
        char line_copy[1024];
      strcpy(line_copy, line);
      char *i = strtok(line_copy, " ");
        if(strcmp("float", i)==0 || strcmp("float*",i)==0){
        func = add_float_pointer_to_func_heap(func, line);
      }else if(strcmp("char", i)==0 || strcmp("char*",i)==0){
        func = add_char_pointer_to_func_heap(func, line);
      }else if(strcmp("int", i)==0 || strcmp("int*",i)==0){
        func = add_int_pointer_to_func_heap(func, line);
      }
      }
      return head;
}

bool check_literal(char *line){
  int n = 0;
  for (int i = 0;i<strlen(line);i++){
    if(line[i]=='"'){
      n++;
    }
  }
  if(n==2){
    return true;
  }
  else{
    return false;
  }
}

HeapNode *push_malloc(HeapNode *head, char *line, bool in_function, Func_Node *func, Var_Node *var){
 char NAME[1024];
  char type[1024];
  line[strcspn(line, ";")] = 0;

  char *a = strstr(line, "malloc");
  char *b = strstr(a, "(");

  int i;
  for(i = 1; i<strlen(b); i++){
    if(b[i]=='('){
      break;
    }
  }
  for(int x = i+1, j=0; i<strlen(b);x++,j++){
    if(b[x]==')'){
      type[j] = '\0';
      break;
    }
    type[j] = b[x];
  }
  


  for(int z = 1, p=0; z<strlen(b)-1;p++, z++){
    NAME[p] = b[z];
    NAME[p+1] = '\0';
  }

  char s[1024];
  strcpy(s, NAME);



  char copy[1024];
  strcpy(copy, line);
  
  copy[strcspn(copy, "=")] = 0;
    char *c = removewhitespace(copy);
    char *tok = strtok(c, " ");
    
    while(tok!=NULL){

      
      if(strcmp(tok, "int")!=0 && strcmp(tok, "int*")!=0 && strcmp(tok, "char")!=0 && strcmp(tok, "char*")!=0 && strcmp(tok, "float*")!=0 && strcmp(tok, "float")!=0){
      break;}
      tok = strtok(NULL, " ");
      
    }
  strcat(NAME, ")");
  delete_character(tok, '*');
      if(!in_function){
      delete_character(type, '*');
      head = push_heap(head, type, tok, s, "global");
      char line_copy[1024];
      strcpy(line_copy, line);
      char *i = strtok(line_copy, " ");
        if(strcmp("float", i)==0 || strcmp("float*",i)==0){
        int size = sizeof(float*);
        char s[1024];
        sprintf(s, "%d", size);
        delete_character(NAME, '*');
        var = push_variable(var, "float*", tok, s);
      }else if(strcmp("char", i)==0 || strcmp("char*",i)==0){
        int size = sizeof(char*);
        char s[1024];
        sprintf(s, "%d", size);
        delete_character(NAME, '*');
        var = push_variable(var, "char*", tok, s);
      }else if(strcmp("int", i)==0 || strcmp("int*",i)==0){
        int size = sizeof(int*);
        char s[1024];
        sprintf(s, "%d", size);
        delete_character(NAME, '*');
        var = push_variable(var, "int*", tok, s);
      }
      
      }else{
        Func_Node *ptr = func;
        while(ptr->next!=NULL){
          ptr = ptr->next;
        }
        head = push_heap(head, type, tok, s, ptr->name);
        char line_copy[1024];
      strcpy(line_copy, line);
      char *i = strtok(line_copy, " ");
        if(strcmp("float", i)==0 || strcmp("float*",i)==0){
        func = add_float_pointer_to_func_heap(func, line);
      }else if(strcmp("char", i)==0 || strcmp("char*",i)==0){
        func = add_char_pointer_to_func_heap(func, line);
      }else if(strcmp("int", i)==0 || strcmp("int*",i)==0){
        func = add_int_pointer_to_func_heap(func, line);
      }
      }
      return head;
}

RONode *push_ro(RONode *head, char *line, bool in_function, Func_Node *func){
  char line_copy[1024];
  strcpy(line_copy, line);
  RONode *new = (RONode*)calloc(1, sizeof(RONode));
  line[strcspn(line, ";")] = 0;
  char *a = strchr(line, '"');
  delete_character(a, '"');
  int n = strlen(a);
  char *name = strtok(line_copy, " ");
  while(name!=NULL){
    if(strcmp(name, "char")!=0 && strcmp("char*", name)!=0 && strcmp(name, "*")!=0){
      break;
    }
    name = strtok(NULL, " ");
  }
  delete_character(name, '*');

  char size[1024];
  sprintf(size, "%d", n);
  strcat(size, "*sizeof(char)");
    removewhitespace(name);
  strcpy(new->name, name);
  strcpy(new->size, size);
  strcpy(new->type, "char*");
  new->next = NULL;

  if(in_function){
    
    Func_Node *var = func;
    while(var->next!=NULL){
      var = var->next;
    }
    strcpy(new->scope, var->name);
    RONode *ptr = head;
    if(ptr==NULL){
      return new;
    }
    while(ptr->next!=NULL){
      ptr = ptr->next;
    }
    ptr->next = new;
  }else{
    strcpy(new->scope, "global");
    RONode *ptr = head;
    if(ptr==NULL){
      return new;
    }
    while(ptr->next!=NULL){
      ptr = ptr->next;
    }
    ptr->next = new;
  }
  return head;
}


void printROdata(RONode *head){
  RONode *ptr = head;
  printf("### ROData ###       scope type  size\n");
  while(ptr!=NULL){
    printf("   %s   %s  %s  %s\n", ptr->name, ptr->scope, ptr->type, ptr->size);
  ptr = ptr->next;
  }
  printf("\n");
}

void printFuncVariables(Func_Node *head){
  printf("  - Total number of variables per function:\n");
  Func_Node *ptr = head;
  while(ptr!=NULL){
    printf("    %s: ", ptr->name);
    int num = 0;
    Var_Node *p = ptr->var;
    while(p!=NULL){
      num++;
      p = p->next;
    }
    printf("%d\n", num);
    ptr = ptr->next;
  }
}

int count(char *line, char c){
  int num = 0;
  for(int i = 0;i<strlen(line);i++){
    if(line[i]==c){
      num++;
    }
  }
  return num;
}

void freenodes(Func_Node *func, RONode *ro, Var_Node *var, HeapNode *heap){
  Var_Node * v = NULL;
  Var_Node *vv = NULL;
  v = var;
  while(v!=NULL){
    vv = v;
    v = v->next;
    free(vv);
  }
  RONode * r = NULL;
  RONode *rr = NULL;
  r = ro;
  while(r!=NULL){
    rr = r;
    r = r->next;
    free(rr);
  }
  Func_Node * f = NULL;
  Func_Node *ff = NULL;
  f = func;
  while(f!=NULL){
    ff = f;
    f = f->next;
    free(ff);
  }
  HeapNode * h = NULL;
  HeapNode *hh = NULL;
  h = heap;
  while(h!=NULL){
    hh = h;
    h = hh->next;
    free(hh);
  }
}


int main(int argc, char **argv){
  Var_Node *static_data = NULL;
  Func_Node *func_data = NULL;
  RONode * ro_data = NULL;
  HeapNode *heap_data = NULL;
  bool static_int = false;
  bool static_float = false;
  bool static_char = false;
  bool static_int_pointer = false;
  bool static_float_pointer = false;
  bool string_literal = false;
  bool in_function = false;

  int brackets = 0;
    FILE* file;
    file = fopen(argv[1], "r");
    if(file==NULL){
      fprintf(stderr, "Couldn't find file in current directory\n");
      return -1;
    }
    char x[1024];
    char x_copy[1024];
    char x_func[1024];
    int lines = 0;
    while (fgets(x, sizeof(x), file)) {
             if(brackets>0){
                    lines++;
                    }
        int j = count(x, '{');
        int k = count(x, '}');
          brackets-=k;
          brackets+=j;
        if(is_empty(x)==0 && !checkPrintf(x)){
        x[strcspn(x, "\n")] = 0;
        strcpy(x_copy, x);


        if(checkMalloc(x)){
          heap_data = push_malloc(heap_data, x, in_function, func_data, static_data);
        }
        if(check_literal(x) && !check_brackets(x) && !check_parentheses(x) && !checkMalloc(x) && !checkCalloc(x)){
          ro_data= push_ro(ro_data, x, in_function, func_data);
        }
        if(checkCalloc(x)){
          
          heap_data = push_calloc(heap_data, x, in_function, func_data, static_data);
        }
        char *piece = strtok(x_copy, " ");
        
        

                  
        if(strchr(x, '}')!=NULL){
          if(brackets==0){
          func_data = addFuncLines(func_data, lines);
          lines = 0;
          }
        }
        while(piece!=NULL){   
          if(static_int && !in_function){
            if(check_star(x)){
              
              static_int_pointer = true;
            }else{
            strcpy(x_func, x);       
            char copy[1024];
            strcpy(copy, x);
              static_data=add_int(static_data, x_func);
            }static_int = false;
          }
          if(static_int && in_function && (!check_parentheses(x))){
            strcpy(x_func, x);
            func_data = add_int_to_func(func_data, x_func);
            static_int = false;
          }
          if(static_float && in_function && (!check_parentheses(x))){
            strcpy(x_func, x);
            func_data = add_float_to_func(func_data, x_func);
            static_float = false;
          }
          if(static_char && in_function && (!check_parentheses(x))){
            strcpy(x_func, x);
            func_data = add_char_to_func(func_data, x_func);
            static_char = false;
          }
          if(static_int_pointer && in_function && (!check_parentheses(x))){
            strcpy(x_func, x);
            func_data = add_int_pointer_to_func(func_data, x_func);
            static_int_pointer = false;
          }
          if(static_float_pointer && in_function && (!check_parentheses(x))){
            strcpy(x_func, x);
            func_data = add_float_pointer_to_func(func_data, x_func);
            static_float_pointer = false;
          }
          if(string_literal && in_function && (!check_parentheses(x))){
            strcpy(x_func, x);
            func_data = add_char_pointer_to_func(func_data, x_func);
            string_literal = false;
          }
          if(static_float && !in_function){
            if(check_star(x)){
              static_float_pointer = true;
            }else{
            strcpy(x_func, x);
            static_data=add_float(static_data, x_func);
            }static_float = false;
          }
          if(string_literal && strcmp(piece, "char*")!=0 && !in_function){
            strcpy(x_func, x);
            static_data=add_string_literal_to_stack(static_data, x_func);
            string_literal = false;
          }
          if(static_float_pointer && strcmp(piece, "float*")!=0 && !in_function){
            strcpy(x_func, x);
            static_data=add_float_pointer(static_data, x_func);
            static_float_pointer = false;
          }
          if(static_int_pointer && !in_function){
            strcpy(x_func, x);
            static_data=add_int_pointer(static_data, x_func);
            static_int_pointer = false;
          }
          if(static_char && strcmp(piece, "char")!=0 && !in_function){
            strcpy(x_func, x);
            static_data=add_char(static_data, x_func);
            static_char = false;
          }
          
          if(*piece == '{') {
                       Func_Node *ptr = func_data;
              while(ptr!=NULL && ptr->next!=NULL){
                
                ptr = ptr->next;  
              }
              ptr->curr=true;
              
            in_function = true;
          }
          if(*piece == '}'){
            Func_Node *ptr = func_data;
              while(ptr!=NULL){
                ptr->curr=false;
                ptr = ptr->next;  
              }   
          }
          if(strcmp("int", piece)==0 && !check_star(x)){
            if(!check_parentheses(x)){
              static_int = true;}
          }
          if(strcmp("char", piece)==0){
            if(!check_parentheses(x) && !check_star(x)){
              static_char = true;
              }
            else if(!check_parentheses(x) && check_star(x)){
              string_literal = true;
            }
          }
          if(strcmp("float", piece)==0 && !check_star(x)){
            if(!check_parentheses(x)){static_float = true;}
          }
          if((strcmp("int*", piece)==0 || (strcmp("int", piece)==0)) && check_star(x)){
            if(!check_parentheses(x)){static_int_pointer = true;}
          }
          if((strcmp("float*", piece)==0 || (strcmp("float", piece)==0)) && check_star(x)){
            if(!check_parentheses(x)){static_float_pointer = true;}
          }
          if(strcmp("char*", piece)==0){
            if(!check_parentheses(x)){string_literal = true;}
          }
          if((strcmp("int", piece)==0 || strcmp("float", piece)==0 || strcmp("void", piece)==0 || strcmp("char*", piece)==0 || strcmp("char", piece)==0 || strcmp("int*", piece)==0 || strcmp("float*", piece)==0) && !checkCalloc(x) && !checkMalloc(x)){
            if(check_parentheses(x) && !check_brackets(x)){
              in_function = true;
               in_function = true;
              strcpy(x_func, x);
              
              func_data = add_function(func_data, x);
                       Func_Node *ptr = func_data;
              while(ptr!=NULL && ptr->next!=NULL){
                
                ptr = ptr->next;  
              }
              ptr->curr=true;
              
              func_data = add_parameters(func_data, x_func);
            }
          }
          piece = strtok(NULL, " ");
        }
    } 
    }
  fclose(file);   
  printProgramName(argv[1]);  
  printROdata(ro_data);
  printGlobalVariables(static_data); 
  printHeapData(heap_data);
  printUnusedSpace();
  printStack(func_data);
  printf("**** STATS ****\n");
  printNumFileLines(argv[1]);
  printFunctionNames(func_data);
  printFuncLines(func_data);
  printFuncVariables(func_data);
  printf("//////////////////////////////\n");

  freenodes(func_data, ro_data, static_data, heap_data);
    return 0;
}




