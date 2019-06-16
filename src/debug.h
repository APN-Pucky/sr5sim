
#include <string>
#ifndef NDEBUG
#include <iostream>
#endif
extern signed debug_print;
extern unsigned debug_cached;
extern bool debug_line;
extern std::string debug_str;
#ifndef NDEBUG
#if defined(__GNUC__) || defined(__GNUG__)
#define _DEBUG_MSG(v, format, ...)                                  \
    {                                                                   \
       if(debug_print >= v)                   \
	         {                                                               \
		                if(debug_cached) {                                     \
				                char buf[4096];                                         \
						                if(debug_line){ snprintf(buf, sizeof(buf), "%i - " format, __LINE__, __VA_ARGS__);}  \
								                  else { snprintf(buf, sizeof(buf), format, __VA_ARGS__); }            \
										                  debug_str += buf;                                       \
												              }                                                           \
													                  else { if(debug_line){ printf("%i - " format, __LINE__ , __VA_ARGS__);} \
															                     else {printf(format, __VA_ARGS__);}                             \
																	                 std::cout << std::flush;  }                                  \
																			         }                                                               \
																				     }
																				     #define _DEBUG_SELECTION(format, ...)                               \
																				         {                                                                   \
																					         if(debug_print >= 2)                       \
																						         {                                                               \
																							             _DEBUG_MSG(2, "Possible targets of " format ":\n", __VA_ARGS__); \
																								                 fd->print_selection_array();                                \
																										         }                                                               \
																											     }
#define _DEBUG_ASSERT(expr) { assert(expr); }
#elif defined(_MSC_VER)

#define _DEBUG_MSG(v, format, ...)                                  \
    {                                                                   \
       if(debug_print >= v)                   \
	         {                                                               \
		                if(debug_cached) {                                     \
				                char buf[4096];                                         \
						                if(debug_line){ snprintf(buf, sizeof(buf), "%i - " format, __LINE__, __VA_ARGS__);}  \
								                  else { snprintf(buf, sizeof(buf), format, __VA_ARGS__); }            \
										                  debug_str += buf;                                       \
												              }                                                           \
													                  else { if(debug_line){ printf("%i - " format, __LINE__ , __VA_ARGS__);} \
															                     else {printf(format, __VA_ARGS__);}                             \
																	                 std::cout << std::flush;  }                                  \
																			         }                                                               \
																				     }
																				     #define _DEBUG_SELECTION(format, ...)                               \
																				         {                                                                   \
																					         if(debug_print >= 2)                       \
																						         {                                                               \
																							             _DEBUG_MSG(2, "Possible targets of " format ":\n", __VA_ARGS__); \
																								                 fd->print_selection_array();                                \
																										         }                                                               \
																											     }
																											     #define _DEBUG_ASSERT(expr) { assert(expr); }

#else
#endif

																											     #else
																											     #define _DEBUG_MSG(v, format, args...)
																											     #define _DEBUG_SELECTION(format, args...)
																											     #define _DEBUG_ASSERT(expr)
																											     #endif

