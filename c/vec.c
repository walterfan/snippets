#include <stdio.h>
#include <stdlib.h>

#define NULL 0
#define IDENT 0
#define OP +

typedef int data_t;

typedef struct {
	long int len;
	data_t *data;
} vec_rec, *vec_ptr;

vec_ptr new_vec(long int len) {
	vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
	if(!result)
		return NULL;
	result->len = len;

	if(len > 0) {
		data_t *data = (data_t*) calloc(len, sizeof(data_t));
		if(!data) {
			free((void*)result);
			return NULL;
		}
		result->data = data;
	} else {
		result->data = NULL;
	}
	return result;
}

int get_vec_element(vec_ptr v, long int index, data_t *dest) {
	if(index < 0 || index >= v->len) {
		return 0;
	}
	*dest = v->data[index];
	return 1;
}

long int vec_length(vec_ptr v) {
	return v->len;
}

data_t *get_vec_start(vec_ptr v) {
	return v->data;
}

void combine1(vec_ptr v, data_t *dest) {
	long int i;

	*dest = IDENT;
	for(i=0; i<vec_length(v);i++) {
		data_t val;
		get_vec_element(v, 1, &val);
		*dest = *dest OP val;
	}
}

void combine2(vec_ptr v, data_t *dest) {
	long int i;
	long int length = vec_length(v);

	*dest = IDENT;
	for(i=0; i<length;i++) {
		data_t val;
		get_vec_element(v, 1, &val);
		*dest = *dest OP val;
	}
}

void combine3(vec_ptr v, data_t *dest) {
	long int i;
	long int length = vec_length(v);
	data_t *data = get_vec_start(v);

	*dest = IDENT;
	for(i=0; i<length;i++) {
		data_t val;
		*dest = *dest OP data[i];
	}
}

void combine4(vec_ptr v, data_t *dest) {
	long int i;
	long int length = vec_length(v);
	data_t *data = get_vec_start(v);

	data_t acc = IDENT;

	for(i=0; i<length;i++) {
		data_t val;
		acc = acc OP data[i];
	}
	*dest = acc;
}

int main(int argc, char* argv[]) {
	int vec_len = 10000;
	if(argc > 1) {
		vec_len = atoi(argv[1]);
	}
	vec_ptr aVecPtr = new_vec(vec_len);
	data_t aVar = 123;
	combine1(aVecPtr, &aVar);
	printf("--- done ---");	
	return 0;
}