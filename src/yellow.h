
#define NULLABLE
#define OUT

#define IS_DIVISBLE_BY(a, b) (!(a % b))
#define ARRAY_COUNT(x) ((sizeof(x)/sizeof(0[x])) /\
					 ((size_t)IS_DIVISBLE_BY(sizeof(x), sizeof(0[x]))))