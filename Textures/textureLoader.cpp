#include <GL/freeglut.h>
#include "textureLoader.hpp"
#include <stdio.h>
#include <stdlib.h>

GLuint loadTexture(const char *filename, int width, int height)
{
  FILE * file = fopen(filename, "rb");
  if (file == NULL) return 0;
  // width = 1024;
  // height = 512;
  unsigned char *data = (unsigned char*) malloc(width * height * 3);
  fread(data, width * height * 3, 1, file);
  fclose(file);

  for (int i = 0; i < width * height; i ++)
  {
    int index = i*3;
    unsigned char B, R;
    B = data[index], R = data[index+2];
    data[index] = R, data[index+2] = B;
  }


  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
  free(data);

  return texture;
}