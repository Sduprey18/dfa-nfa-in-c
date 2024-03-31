#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dfa.h"
#define DFA_NSYMBOLS 128

DFA newDFA(int numstates){
  
  DFA dfa = (DFA)malloc(sizeof(struct dfa));
  
  dfa->currentState = 0;
  dfa->numstates = numstates;
  
  dfa->TRANSITION_TABLE = (int**)malloc(numstates * sizeof(int*));
  for (int i=0; i<numstates; i++){
    
  }
  
  for(int i=0; i<numstates; i++){
    dfa->TRANSITION_TABLE[i] = (int *)malloc(128 * sizeof(int));
    for(int j=0; j<128; j++){
      dfa->TRANSITION_TABLE[i][j] = 0;
    }
  }
  
  dfa->ACCEPT_TABLE = (bool*)malloc(numstates * sizeof(bool));
  
  for(int i=0; i<numstates; i++){
    dfa->ACCEPT_TABLE[i] = false;
  }
  return dfa;
}

void freeDFA(DFA dfa){
    for (int i = 0; i < dfa->numstates; i++) {
        free(dfa->TRANSITION_TABLE[i]);
    }
    free(dfa->TRANSITION_TABLE);
    free(dfa->ACCEPT_TABLE);
    free(dfa->DESCRIPTION);
    free(dfa);
}

int DFAsize(DFA dfa){
    return dfa->numstates;
}

char* DFA_get_description(DFA dfa){
    return dfa->DESCRIPTION;
}

void DFA_set_description(DFA dfa, char* str){
    dfa->DESCRIPTION = strdup(str);
}

int DFA_get_transition(DFA dfa, int src, char sym){
    return dfa -> TRANSITION_TABLE[src][(int)sym];
}

void DFA_set_transition(DFA dfa, int src, char sym, int dst){
    ///dfa->TRANSITION_TABLE[src][sym] = dst;
    dfa->TRANSITION_TABLE[src][(unsigned char)sym] = dst;
}

void DFA_set_transition_str(DFA dfa, int src, char *str, int dst){
    for(int i=0; str[i] != '\0'; i++) {
		dfa->TRANSITION_TABLE[src][i] = dst;
	}
}

void DFA_set_transition_all(DFA dfa, int src, int dst){
    for(int j=0; j<128; j++){
    dfa->TRANSITION_TABLE[src][j] = dst;
  }
}

void DFA_set_accepting(DFA dfa, int state, bool value){
    dfa->ACCEPT_TABLE[state] = value;
}

bool DFA_get_accepting(DFA dfa, int state){
    return dfa->ACCEPT_TABLE[state];
}

bool DFA_execute(DFA dfa, char *input){
    int state = dfa->currentState;
    for(int i = 0; i<strlen(input);i++){
        state = DFA_get_transition(dfa, state, input[i]);
    }
    return DFA_get_accepting(dfa, state);
}