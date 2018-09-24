class sockets
{
    public:
        static const char *className;
        static Lunar<sockets>::RegType methods[];

        sockets(lua_State *L){ memset( buffer, '\0', sizeof(buffer)); }
        int socket(lua_State *L)
        {
            int domain = luaL_checkint(L, 1);
            int type = luaL_checkint(L, 2);
            int protocol = luaL_checkint(L, 3);
            int retval = ::socket(domain, type, protocol);
            sa.sin_family = domain;
            lua_pushnumber(L, retval);
            return 1;
        }

        int gethostbyname(lua_State *L)
        {
            const char *hostname = luaL_checkstring(L, 1);
            he = ::gethostbyname(hostname);
            bcopy(*he->h_addr_list, (char *)&sa.sin_addr.s_addr, sizeof(sa.sin_addr.s_addr));
            return 0;
        }

        int setport(lua_State *L)
        {
            int port = luaL_checkint(L, 1);
            sa.sin_port = htons(port);
            return 0;
        }

        int connect(lua_State *L)
        {
            int socknum = luaL_checkint(L, 1);
            int retval = ::connect(socknum, (struct sockaddr *)&sa, sizeof(sa));
            lua_pushnumber(L, retval);
            return 1;
        }

        int send(lua_State *L)
        {
            int socknum = luaL_checkint(L, 1);
            const char *data = lua_tostring(L, 2);
            int retval = ::write(socknum, data, strlen(data));
            lua_pushnumber(L, retval);
            return 1;
        }

        int read(lua_State *L)
        {
            int socknum = luaL_checkint(L, 1);
            int retval = ::read(socknum, buffer, sizeof(buffer));
            if(retval > 0)
            {
                lua_pushstring(L, buffer);
                memset( buffer, '\0', sizeof(buffer));
                return 1;
            }
            return 0;
        }

        int listen(lua_State *L)
        {
            int socknum = luaL_checkint(L, 1);
            int retval = ::listen(socknum,1024);
            lua_pushnumber(L, retval);
            return 1;
        }

        int accept(lua_State *L)
        {
            int socknum = luaL_checkint(L, 1);
            int retval = ::accept(socknum, NULL, NULL);
            lua_pushnumber(L, retval);
            return 1;
        }

        int bind(lua_State *L)
        {
            int socknum = luaL_checkint(L, 1);
            int retval = ::bind(socknum, (struct sockaddr *)&sa, sizeof(sa));
            lua_pushnumber(L, retval);
            return 1;
        }

        int setaddr(lua_State *L)
        {
            int addr = luaL_checkint(L, 1);
            sa.sin_addr.s_addr = htonl(addr);
            return 0;
        }

    private:
        char buffer[4096];
        struct sockaddr_in sa;
        struct hostent *he;
};
