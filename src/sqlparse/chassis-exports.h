
#ifndef _CHASSIS_EXPORTS_
#define _CHASSIS_EXPORTS_

#if defined(_WIN32)

#if defined(mysql_chassis_EXPORTS)
#define CHASSIS_API __declspec(dllexport)
#elif defined(mysql_chassis_STATIC)
#define CHASSIS_API 
#else
#define CHASSIS_API extern __declspec(dllimport)
#endif

#else

#define CHASSIS_API		extern

#endif

#endif

