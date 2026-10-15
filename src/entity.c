#include "entity.h"

//local 
#include "game.h"

//external 
#include "raylib.h"
#include <stdlib.h>
#include <stddef.h>

Entity
*LoadEntityRec(float x, float y, float w, float h, Color col)
{
  Entity *entity = MemAlloc(sizeof(Entity));

  entity->type = ENTITY_TYPE_REC;

  entity->x = x;
  entity->y = y;
  entity->w = w;
  entity->h = h;

  entity->atr.rec_color = col;

  return entity;
}

Entity
*LoadEntityTex(float x, float y, float w, float h, const char *pathToTexture)
{
  Entity *entity = MemAlloc(sizeof(Entity));

  entity->type = ENTITY_TYPE_TEX;

  entity->x = x;
  entity->y = y;
  entity->w = w;
  entity->h = h;

  entity->atr.tex_texture = LoadTexture(pathToTexture);

  return entity;
}

Entity
*LoadEntityLabel(float x, float y, const char *str, float fontSize)
{
  Entity *entity = MemAlloc(sizeof(Entity));

  entity->type = ENTITY_TYPE_LABEL;

  entity->x = x;
  entity->y = y;

  entity->atr.label.str = str;
  entity->atr.label.fontSize = fontSize;
  entity->atr.label.fontSpacing = fontSize / 10.0;

  Vector2 labelSize = MeasureTextEx(*GetGameFont(), entity->atr.label.str, entity->atr.label.fontSize, entity->atr.label.fontSpacing);

  entity->w = labelSize.x;
  entity->h = labelSize.y;

  return entity;
}

void
UnloadEntity(Entity *entity)
{
  if (entity != NULL)
  {
    if (entity->type == ENTITY_TYPE_TEX) UnloadTexture(entity->atr.tex_texture);

    MemFree(entity);

    entity = NULL;
  }
}

void
DrawEntity(Entity *entity)
{
  switch (entity->type)
  {
    case ENTITY_TYPE_TEX:
    {
        DrawTexturePro(entity->atr.tex_texture, (Rectangle){0, 0, entity->atr.tex_texture.width, entity->atr.tex_texture.height}, 
                       (Rectangle){entity->x, entity->y, entity->w, entity->h}, (Vector2){0}, 0, WHITE);
    }
    break;
    case ENTITY_TYPE_REC:
    {
        DrawRectangle(entity->x, entity->y, entity->w, entity->h, entity->atr.rec_color);
    }
    break;
    case ENTITY_TYPE_LABEL:
    {
        DrawTextEx(*GetGameFont(), entity->atr.label.str, (Vector2){entity->x, entity->y}, entity->atr.label.fontSize, entity->atr.label.fontSpacing, WHITE);
    }
  }
}
