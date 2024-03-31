/*
 * File: IntSet2.c
 * Creator: George Ferguson
 * Created: Thu Aug  3 17:36:24 2017
 * Time-stamp: <Tue Aug  8 10:11:39 EDT 2017 ferguson>
 *
 * IntSet implemented as a bit vector.
 * Using long long should allow values from 0 to 63.
 */

#include <stdlib.h>
#include <stdio.h>
#include "IntSet.h"

typedef unsigned long long int intset_t;

struct IntSet {
    intset_t bits;
};

#define NUMBITS (sizeof(intset_t)*8)

/**
 * Allocate, initialize and return a new (empty) IntSet.
 */
IntSet
IntSet_new() {
    IntSet this = (IntSet)malloc(sizeof(struct IntSet));
    this->bits = 0;
    return this;
}

/**
 * Free the memory used for the given IntSet and all its elements.
 */
void
IntSet_free(IntSet set) {
    if (set != NULL) {
	free(set);
    }
}

/**
 * Return true if the given IntSet is empty.
 */
bool
IntSet_is_empty(const IntSet set) {
    return set->bits == 0;
}

/**
 * Add given int to the given IntSet (if it's not already there).
 * We keep the list sorted (so it prints nicely).
 */
void
IntSet_add(IntSet set, int value) {
    // Range check
    if (value < 0 || value >= NUMBITS) {
	fprintf(stderr, "IntSet_add: value out of range: %d\n", value);
	abort();
    }
    set->bits |= (1L << value);
}

/**
 * Return true if the given IntSet contains the given int value.
 */
bool
IntSet_contains(const IntSet set, int value) {
    return set->bits & (1L << value);
}

/**
 * Add the contents of IntSet set2 to IntSet set1 (adding those elements
 * that aren't already in set1). This will modify set1 unless set2 is empty
 * (or all its elements are already in set1).
 */
void
IntSet_union(IntSet set1, const IntSet set2) {
    set1->bits |= set2->bits;
}

/**
 * Return true if the first IntSet contains every member of the second
 * IntSet.
 */
bool
IntSet_contains_all(IntSet set1, IntSet set2) {
    return (set1->bits | set2->bits) == set1->bits;
}

/**
 * Return true if the two given IntSets contain exactly the same members,
 * otherwise false.
 */
bool
IntSet_equals(IntSet set1, IntSet set2) {
    return set1->bits == set2->bits;
}

/**
 * Call the given function on each element of given IntSet, passing the
 * int value to the function.
 */
void
IntSet_iterate(const IntSet set, void (*func)(int)) {
    for (int i=0; i < NUMBITS; i++) {
	if (IntSet_contains(set, i)) {
	    func(i);
	}
    }
}

struct IntSetIterator {
    IntSet set;
    int index;
};

/**
 * Return an IntSetIterator for the given IntSet.
 * Don't forget to free() this when you're done iterating.
 */
IntSetIterator
IntSet_iterator(const IntSet set) {
    IntSetIterator iterator = (IntSetIterator)malloc(sizeof(struct IntSetIterator));
    iterator->set = set;
    iterator->index = 0;
    return iterator;
}

/**
 * Return true if the next call to IntSetIterator_next on the given
 * IntSetIterator will not fail.
 */
bool
IntSetIterator_has_next(const IntSetIterator iterator) {
    while (iterator->index < NUMBITS) {
	if (IntSet_contains(iterator->set, iterator->index)) {
	    return true;
	} else {
	    iterator->index += 1;
	}
    }
    return false;
}

/**
 * Return the next int in the IntSet underlying the given IntSetIterator,
 * or -1 if there is no such element.
 */
int
IntSetIterator_next(IntSetIterator iterator) {
    if (IntSetIterator_has_next(iterator)) {
	// iterator index will point to next 1 bit
	int value = iterator->index;
	iterator->index += 1;
	return value;
    } else {
	return -1;
    }
}

/**
 * Print the given IntSet to stdout.
 */
void
IntSet_print(IntSet set) {
    IntSetIterator iterator = IntSet_iterator(set);
    printf("{");
    while (IntSetIterator_has_next(iterator)) {
	int value = IntSetIterator_next(iterator);
	printf("%d", value);
	if (IntSetIterator_has_next(iterator)) {
	    printf(",");
	}
    }
    printf("}");
    free(iterator);
}

#include <string.h>

/**
 * Return the string representation of the given IntSet.
 * Don't forget to free() this string.
 */
char *
IntSet_to_string(IntSet set) {
    char *result = NULL;
    IntSetIterator iterator = IntSet_iterator(set);
    while (IntSetIterator_has_next(iterator)) {
	int value = IntSetIterator_next(iterator);
	char buf[8];
	sprintf(buf, "%d", value);
	if (IntSetIterator_has_next(iterator)) {
	    strcat(buf, ",");
	}
	if (result == NULL) {
	    result = malloc(strlen(buf)+1);
	    strcpy(result, buf);
	} else {
	    char *old_result = result;
	    result = (char*)malloc(strlen(old_result)+strlen(buf)+1);
	    strcpy(result, old_result);
	    strcat(result, buf);
	    free(old_result);
	}
    }
    free(iterator);
    return result;
}