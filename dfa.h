#ifndef DFA_H
#define DFA_H

#include <stdbool.h>

struct dfa {
  char* DESCRIPTION;
  int currentState;
  int numstates;
  bool* ACCEPT_TABLE;
  int** TRANSITION_TABLE;
};

typedef struct dfa *DFA;

extern DFA newDFA(int numstates);

extern void freeDFA(DFA dfa);

extern int DFAsize(DFA dfa);

extern char* DFA_get_description(DFA dfa);

extern void DFA_set_description(DFA dfa, char* str);

extern int DFA_get_transition(DFA dfa, int src, char sym);

extern void DFA_set_transition(DFA dfa, int src, char sym, int dst);

extern void DFA_set_transition_str(DFA dfa, int src, char *str, int dst);

extern void DFA_set_transition_all(DFA dfa, int src, int dst);

extern void DFA_set_accepting(DFA dfa, int state, bool value);

extern bool DFA_get_accepting(DFA dfa, int state);

extern bool DFA_execute(DFA dfa, char *input);

extern void DFA_print(DFA dfa);

#endif