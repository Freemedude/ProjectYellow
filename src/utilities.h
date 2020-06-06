#define NULLABLE
#define OUT

#define IS_DIVISBLE_BY(a, b) (!(a % b))
#define ARRAY_COUNT(x) ((sizeof(x)/sizeof(0[x])) /\
					 ((size_t)IS_DIVISBLE_BY(sizeof(x), sizeof(0[x]))))


#define KILOBYTES(Value) ((Value) * 1024)
#define MEGABYTES(Value) (KILOBYTES((Value) * 1024))
#define GIGABYTES(Value) (MEGABYTES((Value) * 1024))

struct Array
{
	u64 count;
	u64 element_size;
	void* data;
};
