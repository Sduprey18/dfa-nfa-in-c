#include <stdio.h>
#include <string.h>
#include "nfa.h"
#include "IntSet.c"

NFA newNFA(int numstates) {
    NFA nfa = (NFA)malloc(sizeof(struct nfa));
    nfa->DESCRIPTION = NULL;
    nfa->CURR_STATES = IntSet_new();
    nfa->NUM_STATES = numstates;
    nfa->ACCEPT_TABLE = (bool*)malloc(numstates * sizeof(bool));

    for (int i = 0; i < numstates; i++) {
        nfa->ACCEPT_TABLE[i] = false;
    }

    nfa->TRANSITION_TABLE = (IntSet**)malloc(numstates * sizeof(IntSet*));
    for (int i = 0; i < numstates; i++) {
        nfa->TRANSITION_TABLE[i] = (IntSet*)malloc(128 * sizeof(IntSet));
        for (int j = 0; j < 128; j++) {
            nfa->TRANSITION_TABLE[i][j] = IntSet_new();
        }
    }

    return nfa;
}

/*void freeNFA(NFA nfa) {
    free(nfa->DESCRIPTION);
    IntSet_free(nfa->CURR_STATES);

    for (int i = 0; i < nfa->NUM_STATES; i++) {
        free(nfa->ACCEPT_TABLE[i]);
        for (int j = 0; j < 128; j++) {
            IntSet_free(nfa->TRANSITION_TABLE[i][j]);
        }
        free(nfa->TRANSITION_TABLE[i]);
    }

    ////free(nfa->ACCEPT_TABLE);
    free(nfa->TRANSITION_TABLE);
    free(nfa);
}*/

void freeNFA(NFA nfa){
  for (int i = 0; i < nfa->NUM_STATES; i++) {
    for(int j=0; j<128; j++){
      IntSet_free(nfa->TRANSITION_TABLE[i][j]);
    }
    free(nfa->TRANSITION_TABLE[i]);
  }
  free(nfa->TRANSITION_TABLE);
  IntSet_free(nfa->CURR_STATES);
  free(nfa->ACCEPT_TABLE);
  free(nfa);
}

void resetNFA(NFA nfa){
    if(nfa->CURR_STATES != NULL){
    IntSet_free(nfa->CURR_STATES);
  }
  nfa->CURR_STATES = IntSet_new();
  IntSet_add(nfa->CURR_STATES, 0);
}

int NFA_size(NFA nfa){
    return nfa->NUM_STATES;
}

char* NFA_get_description(NFA nfa){
    return nfa->DESCRIPTION;
}

void NFA_set_description(NFA nfa, char* str){
    nfa->DESCRIPTION = str;
}

/*IntSet NFA_get_transitions(NFA nfa, int src, char sym){
      return nfa->TRANSITION_TABLE[src][(int)sym];
}*/


IntSet NFA_get_transitions(NFA nfa, int src, char sym){
    ///return nfa->TRANSITION_TABLE[src][sym];
    return nfa->TRANSITION_TABLE[src][(unsigned char)sym];

}

void NFA_add_transition(NFA nfa, int src, char sym, int dst){
///if(!IntSet_contains(nfa->TRANSITION_TABLE[src][sym], dst)){
   if (!IntSet_contains(nfa->TRANSITION_TABLE[src][(unsigned char)sym], dst)) {
    ///IntSet_add(nfa->TRANSITION_TABLE[src][sym], dst);
    IntSet_add(nfa->TRANSITION_TABLE[src][(unsigned char)sym], dst);

  }
}
void NFA_add_transition_str(NFA nfa, int src, char *str, int dst){
    for (size_t i = 0; i < strlen(str); i++) {
        IntSet_add(nfa->TRANSITION_TABLE[src][(int)str[i]], dst);
    }
}

void NFA_add_transition_all(NFA nfa, int src, int dst) {
    for (int j = 0; j < 128; j++) {
        IntSet_add(nfa->TRANSITION_TABLE[src][j], dst);
    }
}

void NFA_set_accepting(NFA nfa, int state, bool value){
    nfa->ACCEPT_TABLE[state] = value;
}

bool NFA_get_accepting(NFA nfa, int state){
    return nfa->ACCEPT_TABLE[state];
}

bool NFA_execute(NFA nfa, char *input) {
    resetNFA(nfa);
    IntSet_add(nfa->CURR_STATES, 0); 

    for (size_t i = 0; i < strlen(input); i++) {
        IntSet nextStates = IntSet_new();

        IntSetIterator iterator = IntSet_iterator(nfa->CURR_STATES);
        while (IntSetIterator_has_next(iterator)) {
            int state = IntSetIterator_next(iterator);
            IntSet transitions = NFA_get_transitions(nfa, state, input[i]);
            IntSet_union(nextStates, transitions);
        }
        free(iterator);

        IntSet_free(nfa->CURR_STATES);
        nfa->CURR_STATES = nextStates;
    }

    bool accepting = false;
    IntSetIterator iterator = IntSet_iterator(nfa->CURR_STATES);
    while (IntSetIterator_has_next(iterator)) {
        int state = IntSetIterator_next(iterator);
        if (NFA_get_accepting(nfa, state)) {
            accepting = true;
            break;
        }
    }
    free(iterator);

    return accepting;
}