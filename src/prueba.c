#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  
  unsigned char c;

  //scanf("%c", &c);

//  int i = c;

  FILE *in = fopen("prueba.txt", "rb");
  FILE *out = fopen("prueba2.txt", "wb");

  /* Seek to the beginning of the file */
  fseek(in, 0, SEEK_SET);

  // while (! EOF) {
  fread(&c, 1, 1, in);
  fwrite(&c, 1, 1, out);

  fread(&c, 1, 1, in);
  fwrite(&c, 1, 1, out);

  fread(&c, 1, 1, in);
  fwrite(&c, 1, 1, out);

  fclose(in);


//  printf("\nLetra: '%c' \n", c);

//  printf(" %c ",164);//imprime una ñ minúscula



  fclose(out);

  return 0;
}