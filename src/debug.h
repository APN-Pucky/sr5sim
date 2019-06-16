
#include <string>
extern signed debug_print;
extern unsigned debug_cached;
extern bool debug_line;
extern std::string debug_str;
#ifndef NDEBUG
#include <iostream>
#define _DEBUG_MSG(v, format, args...)                                  \
    {                                                                   \
            if(__builtin_expect(debug_print >= v, false))                   \
	            {                                                               \
		                if(debug_cached) {                                     \
				                char buf[4096];                                         \
						                if(debug_line){ snprintf(buf, sizeof(buf), "%i - " format, __LINE__, ##args);}  \
								                  else { snprintf(buf, sizeof(buf), format, ##args); }            \
										                  debug_str += buf;                                       \
												              }                                                           \
													                  else { if(debug_line){ printf("%i - " format, __LINE__ , ##args);} \
															                     else {printf(format, ##args);}                             \
																	                 std::cout << std::flush;  }                                  \
																			         }                                                               \
																				     }
																				     #define _DEBUG_SELECTION(format, args...)                               \
																				         {                                                                   \
																					         if(__builtin_expect(debug_print >= 2, 0))                       \
																						         {                                                               \
																							             _DEBUG_MSG(2, "Possible targets of " format ":\n", ##args); \
																								                 fd->print_selection_array();                                \
																										         }                                                               \
																											     }
																											     #define _DEBUG_ASSERT(expr) { assert(expr); }
																											     #else
																											     #define _DEBUG_MSG(v, format, args...)
																											     #define _DEBUG_SELECTION(format, args...)
																											     #define _DEBUG_ASSERT(expr)
																											     #endif

