#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

#define TMP_STR_SIZE 256

image_t *creer_image()
{
  image_t *image = malloc (sizeof (image_t));
  image->w = 0;
  image->h = 0;
  image->buff = NULL;

  return image;
}

void detruire_image(image_t *p)
{
  free (p->buff);
  free (p);
}

void negatif(image_t *img)
{
  for (int i=0; i < img->w * img->h; i++) {
    img->buff[i] = 255 - img->buff[i];
  } 
}

void modifier_lumin(image_t *img, float pourcent)
{
  for (int i=0; i < img->w * img->h; i++) {
    int temp = img->buff[i] * pourcent;
    if (temp > 255) temp = 255;

    img->buff[i] = temp;
  } 
  
}


image_t *rotation(image_t *src, int angle)
{
  image_t *dst = creer_image();

  if (angle != 90 && angle != 180 && angle != 270) return NULL;

  if (angle == 90 || angle == 270) {
    dst->h = src->w;
    dst->w = dst->h;
  } else {
    dst->w = src->w;
    dst->h = src->h;
  }

  dst->buff = malloc ( (src->w * src->h) * sizeof(unsigned char));
  
  for (int i = 0; i < src->h; i++) {
    for (int j = 0; j < src->w; j++) {
      if (angle == 90)        VAL (dst, j, src->h - i) = VAL (src, i, j);
      else if (angle == 270)  VAL(dst, src->w - j, i) = VAL(src, i, j);
      else                    VAL(dst, src->h - i , src->w - j) = VAL(src, i, j);
    }
  }
  return dst;
}


image_t *charger_image_pgm(char *nom_fichier)
{
  FILE *f;
  image_t *img;
  unsigned int nb_ng;
  char tmp_str[TMP_STR_SIZE];
  enum format {BIN, ASCII} pgm_form;

  /* Ouverture du fichier en lecture */
  f=fopen(nom_fichier, "r");


  if (!f)
    {
      /* on ecrit sur le flux d'erreur */
      fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nom_fichier);
      return NULL;
    }

  /* on lit une ligne en supprimant les eventuels commentaires */
  do
    fgets(tmp_str, TMP_STR_SIZE, f);
  while (*tmp_str == '#');

  /* on determine le format */
  if ( !strcmp(tmp_str, "P5\n"))
    pgm_form = BIN;
  else if ( !strcmp(tmp_str, "P2\n"))
    pgm_form = ASCII;
  else
    {
      fprintf(stderr, "format fichier non pgm\n");
      return NULL;
    }

  img = creer_image();

  /* on lit une ligne en supprimant les eventuels commentaires */
  do
    fgets(tmp_str, TMP_STR_SIZE, f);
  while (*tmp_str == '#');

  /* on determine la largeur et la hauteur de l'image */
  if (sscanf(tmp_str, "%ld %ld\n", &(img->w), &(img->h)) != 2)
    {
      /* si le sscanf n'a pas lu les deux entiers longs attendus: */
      fprintf(stderr, "format fichier non pgm\n");
      detruire_image(img);
      return NULL;
    }

  /* on lit une ligne en supprimant les eventuels commentaires */
  do
    fgets(tmp_str, TMP_STR_SIZE, f);
  while (*tmp_str == '#');

  /* on lit le niveau de gris */
  if (sscanf(tmp_str, " %d ", &nb_ng) != 1)
    {
      /* si le sscanf n'a pas lu l'entier attendu: */
      fprintf(stderr, "format fichier non pgm\n");
      detruire_image(img);
      return NULL;
    }

  if (nb_ng != 255)
    {
      fprintf(stderr, "Nombre de ng different de 255: erreur\n");
      detruire_image(img);
      return NULL;
    }

  /* on alloue l'espace pour stocker l'image */
  img->buff = (unsigned char *) malloc(img->w * img->h * sizeof (unsigned char));

  /* on lit l'image en prenant en compte le format */
  if ( pgm_form == BIN )
    {
      if (fread(img->buff, img->w, img->h, f) != img->h)
        {
          fprintf(stderr, "fichier image imcomplet!\n");
          return NULL;
        }
    }
  else
    {
      unsigned int i,j;
      unsigned char *p = img->buff;
      for ( i = 0; i < img->h; i++)
        for ( j = 0; j < img->w; j++)
          fscanf(f, "%hhu ", p++);
    }

  fclose(f);
  return img;
}

int sauver_image_pgm(char *nom_fichier, image_t *img)
{
  FILE *f;

  f=fopen(nom_fichier, "w");

  if (!f)
    {
      fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nom_fichier);
      return 0;
    }

  fprintf(f, "P5\n");
  fprintf(f, "#Genere par guimp UPMC.\n");
  fprintf(f, "%ld %ld\n", img->w, img->h);
  fprintf(f, "255\n");

  fwrite(img->buff, img->w, img->h, f);
  fclose(f);
  return 1;
}


int main(void) {
  image_t *image = creer_image ();
  image = charger_image_pgm ("quest.pgm");
  image_t *imageRotate = rotation (image, 180);

  sauver_image_pgm ("questRotation.jpg", imageRotate);
  detruire_image (image);
  return 0;
}
