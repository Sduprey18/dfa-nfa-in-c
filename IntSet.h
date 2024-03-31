/*
 * File: IntSet.h
 * Creator: George Ferguson
 * Created: Fri Jul  1 09:41:51 2016
 * Time-stamp: <Fri Aug  4 09:31:27 EDT 2017 ferguson>
 */

#ifndef _IntSet_h
#define _IntSet_h

#include <stdbool.h>

typedef struct IntSet* IntSet;

/**
 * Allocate, initialize and return a new (empty) IntSet.
 */
extern IntSet IntSet_new();

/**
 * Free the memory used for the given IntSet and all its elements.
 */
extern void IntSet_free(IntSet set);

/**
 * Return true if the given IntSet is empty.
 */
extern bool IntSet_is_empty(const IntSet set);

/**
 * Add given int to the given IntSet (if it's not already there).
 */
extern void IntSet_add(IntSet set, int value);

/**
 * Return true if the given IntSet contains the given int value.
 */
extern bool IntSet_contains(const IntSet set, int value);

/**
 * Add the contents of IntSet set2 to IntSet set1 (adding those elements
 * that aren't already in set1). This will modify set1 unless set2 is empty
 * (or all its elements are already in set1).
 */
extern void IntSet_union(IntSet set1, const IntSet set2);

/**
 * Return true if the first IntSet contains every member of the second
 * IntSet.
 */
extern bool IntSet_contains_all(IntSet set1, IntSet set2);

/**
 * Return true if the two given IntSets contain exactly the same members,
 * otherwise false.
 */
extern bool IntSet_equals(IntSet set1, IntSet set2);

/**
 * Call the given function on each element of given IntSet, passing the
 * int value to the function.
 */
extern void IntSet_iterate(const IntSet set, void (*func)(int));

typedef struct IntSetIterator *IntSetIterator;

/**
 * Return an IntSetIterator for the given IntSet.
 * Don't forget to free() this when you're done iterating.
 */
extern IntSetIterator IntSet_iterator(const IntSet set);

/**
 * Return true if the given IntSetIterator will return another element
 * if IntSetIterator_next() is called.
 */
extern bool IntSetIterator_has_next(const IntSetIterator iterator);

/**
 * Return the next int from the given IntSetIterator and increment it
 * to point to the next element.
 * This will cause a crash if there is no such element.
 */
extern int IntSetIterator_next(IntSetIterator iterator);

/**
 * Print the given IntSet to stdout.
 */
extern void IntSet_print(IntSet set);

/**
 * Return the string representation of the given IntSet.
 * Don't forget to free() this string.
 */
extern char *IntSet_to_string(IntSet set);

#endif