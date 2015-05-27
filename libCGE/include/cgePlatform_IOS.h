/*
 * cgePlatforms.h
 *
 *  Created on: 2013-12-31
 *      Author: Wang Yang
 *  Description: load some library and do some essential initialization before compiling.
 */

#ifndef CGEPLATFORMS_H_
#define CGEPLATFORMS_H_

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#include <stdio.h>
#if (defined(DEBUG) || defined(_DEBUG)) && !defined(IOS_NO_LOGINFO)
#define CGE_LOG_INFO(...) printf(__VA_ARGS__)
#else
#define CGE_LOG_INFO(...)
#endif

#if (defined(DEBUG) || defined(_DEBUG))
#define CGE_LOG_ERROR(str, ...) \
do{\
fprintf(stderr, "❌❌❌");\
fprintf(stderr, str, ##__VA_ARGS__);\
fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);\
fprintf(stderr, "❌❌❌\n");\
}while(0)

#define CGE_LOG_CODE(...) __VA_ARGS__

#else

#define CGE_LOG_ERROR(...)
#define CGE_LOG_CODE(...)

#endif

#endif /* HTPLATFORMS_H_ */
