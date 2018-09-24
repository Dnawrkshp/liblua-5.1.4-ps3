#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class surface
{
    public:
        static const char *className;
        static Lunar<surface>::RegType methods[];

        surface(lua_State *L){ }
        int LoadIMG(lua_State *L);
        int DisplayFormat(lua_State *L);
        int getRes(lua_State *L);
        int setRectPos(lua_State *L);
        SDL_Surface *getSurface(){return NewSurface;}
        SDL_Rect *getRect(){return &NewRect;}

    private:
        SDL_Surface *NewSurface;
        SDL_Rect NewRect;
};
