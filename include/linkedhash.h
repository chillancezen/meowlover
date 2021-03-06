// Linked Hash Table implementation.
// v1.0

// The MIT License (MIT)
//
// Copyright (c) 2015 Adrian Bueno Jimenez  (adrian.buenoj@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

struct hashnode_s{
	int key;/*only 4-bytes*/
	void * value;
	struct hashnode_s *next;
};

struct hashtable_s{
	int size;
	struct hashnode_s **table;
};

typedef struct hashnode_s hashnode_t;
typedef struct hashtable_s hashtable_t;


/*
 *
 */
hashtable_t *hashtable_create(int size);

/*
 *
 */
int hashtable_set_key_value(hashtable_t *hashtable, int key, void *value);

/*
 *
 
char*/void *hashtable_get_value(hashtable_t *hashtable, int key);
int hashtable_delete_key(hashtable_t * hashtable,int key);

/*
 *
 */
void hashtable_delete(hashtable_t *hashtable);


#endif
