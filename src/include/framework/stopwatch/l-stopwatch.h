#ifndef __FRAMEWORK_STOPWATCH_L_STOPWATCH_H__
#define __FRAMEWORK_STOPWATCH_L_STOPWATCH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <framework/luahelper.h>

#define	MT_STOPWATCH	"__mt_stopwatch__"

int luaopen_stopwatch(lua_State * L);

#ifdef __cplusplus
}
#endif

#endif /* __FRAMEWORK_STOPWATCH_L_STOPWATCH_H__ */
