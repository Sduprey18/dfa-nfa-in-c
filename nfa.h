#ifndef NFA_H
#define NFA_H

#include <stdbool.h>
#include "IntSet.h"

struct nfa {
  char* DESCRIPTION;
  IntSet CURR_STATES;
  int NUM_STATES;
  bool* ACCEPT_TABLE;
  IntSet** TRANSITION_TABLE;
};

typedef struct nfa *NFA;

extern NFA newNFA(int numstates);

extern void freeNFA(NFA nfa);

extern void resetNFA(NFA nfa);

extern int NFA_size(NFA nfa);

extern char* NFA_get_description(NFA nfa);

extern void NFA_set_description(NFA nfa, char* str);

extern IntSet NFA_get_transitions(NFA nfa, int src, char sym);

extern void NFA_add_transition(NFA nfa, int src, char sym, int dst);

extern void NFA_add_transition_str(NFA nfa, int src, char *str, int dst);

extern void NFA_add_transition_all(NFA nfa, int src, int dst);

extern void NFA_set_accepting(NFA nfa, int state, bool value);

extern bool NFA_get_accepting(NFA nfa, int state);

extern bool NFA_execute(NFA nfa, char *input);

extern void NFA_print(NFA nfa);


#endif