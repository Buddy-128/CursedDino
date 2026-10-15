#ifndef ENTITY_H_
#define ENTITY_H_

#include "raylib.h"

typedef enum EntityType {ENTITY_TYPE_LABEL, ENTITY_TYPE_REC, ENTITY_TYPE_TEX} EntityType;

typedef struct LabelAtr
{
  const char *str;
  float fontSize;
  float fontSpacing;
} LabelAtr;

typedef union EntityAtr 
{
  LabelAtr label;
  Color rec_color;
  Texture tex_texture;
} EntityAtr;

typedef struct Entity 
{
  EntityType type;

  float x;
  float y;
  float w;
  float h;

  EntityAtr atr;
} Entity;

#endif
