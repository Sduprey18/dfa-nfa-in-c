#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dfa.h" 
#include "dfa.c" 
#include "nfa.h"
#include "nfa.c" 


DFA DFA_for_contains_abc() {
    int numStates = 4; 
    DFA dfa = newDFA(numStates);

    
    DFA_set_description(dfa, "dfa for strings containing 'abc'");

    
    DFA_set_transition(dfa, 0, 'a', 1);
    DFA_set_transition(dfa, 1, 'b', 2);
    DFA_set_transition(dfa, 2, 'c', 3);

    
    DFA_set_transition_all(dfa, 3, 0);

    
    DFA_set_accepting(dfa, 3, true);

    DFA_execute(dfa, "abc");

    
    return dfa;
}

DFA DFA_for_dfa(){
    int numStates = 4;
    DFA dfa = newDFA(numStates);

    DFA_set_description(dfa, "exactly the string 'dfa'");

    DFA_set_accepting(dfa, 3,true);

    DFA_set_transition(dfa,0,'d',1);
    DFA_set_transition(dfa,1,'f',2);
    DFA_set_transition(dfa,2,'a',3);

    return dfa;
}

DFA dfa_for_cat(){
    int numStates = 5;
    DFA dfa = newDFA(numStates);

    DFA_set_description(dfa, "strings that start with the sequence 'cat'");

    DFA_set_transition_all(dfa,0,4);
    DFA_set_transition(dfa,0,'c',1);
    DFA_set_transition(dfa,1,'a',2);
    DFA_set_transition(dfa,2,'t',3);
    DFA_set_transition_all(dfa,3,3);

    

    DFA_set_accepting(dfa,3,true);

    return dfa;
}

DFA dfa_for_twos(){
    int numStates = 4;
    DFA dfa = newDFA(numStates);
    DFA_set_description(dfa, "strings containing two ONLY 2's");

    DFA_set_transition(dfa,0,'2',1);
    DFA_set_transition(dfa,1,'2',2);
    DFA_set_transition(dfa,2,'2',3);

    DFA_set_accepting(dfa,2,true);

    return dfa;
}

DFA dfa_for_binary(){

    int numStates =5;
    DFA dfa = newDFA(numStates);
    DFA_set_description(dfa,"strings for even 0's and odd 1's");

    DFA_set_transition(dfa,0,'0',1);
    DFA_set_transition(dfa,1,'0',0);
    DFA_set_transition(dfa,0,'1',0);
    DFA_set_transition(dfa,1,'1',1);

    DFA_set_accepting(dfa,0,true);

    return dfa;
}

bool yesNo(char *x){
    if (strcmp(x, "yes") == 0) {
        return true;
    } else if (strcmp(x, "no") == 0) {
        return false;
    }
    return false;
}

void convert(char *str){
    for(int i =0;i<strlen(str);i++){
        str[i]= tolower(str[i]);
    }
}



NFA ends_in_ked(){
  int size=5;
  NFA nfa = newNFA(size);
  NFA_set_description(nfa, "strings ending in 'ked'");
  NFA_add_transition_all(nfa,0,0);
  NFA_add_transition(nfa,0,'k',1);
  NFA_add_transition(nfa,1,'e',2);
  NFA_add_transition(nfa,2,'d',3);
  NFA_add_transition_all(nfa,3,4);
  NFA_set_accepting(nfa,3,true);
  return nfa;


}

NFA contains_ath(){
  int size = 4;
  NFA nfa = newNFA(size);

  NFA_set_description(nfa, "strings that contain 'ath'");

  NFA_add_transition_all(nfa, 0,0);
  NFA_add_transition(nfa,0,'a',1);
  NFA_add_transition(nfa,1,'t',2);
  NFA_add_transition(nfa,2,'h',3);
  NFA_add_transition_all(nfa,3,3);
  NFA_set_accepting(nfa,3,true);

  return nfa;

}

NFA conference(){
  int size = 17;
  NFA nfa = newNFA(size);

  NFA_set_description(nfa,"trings that have more than one o, f, or r, or more than two c's or n's, or more than there e's ");

  NFA_add_transition(nfa,0,'o',1);
  NFA_add_transition(nfa,1,'o',2);
  NFA_add_transition_all(nfa,2,2);

  NFA_add_transition(nfa,0,'f',3);
  NFA_add_transition(nfa,3,'f',4);
  NFA_add_transition_all(nfa,4,4);

  NFA_add_transition(nfa,0,'r',5);
  NFA_add_transition(nfa,5,'r',6);
  NFA_add_transition_all(nfa,6,6);

  NFA_add_transition(nfa,0,'c',7);
  NFA_add_transition(nfa,7,'c',8);
  NFA_add_transition(nfa,8,'c',9);
  NFA_add_transition_all(nfa,9,9);

  NFA_add_transition(nfa,0,'n',10);
  NFA_add_transition(nfa,10,'n',11);
  NFA_add_transition(nfa,11,'n',12);
  NFA_add_transition_all(nfa,12,12);

  NFA_add_transition(nfa,0,'e',13);
  NFA_add_transition(nfa,13,'e',14);
  NFA_add_transition(nfa,14,'e',15);
  NFA_add_transition(nfa,15,'e',16);
  NFA_add_transition_all(nfa,16,16);

  NFA_set_accepting(nfa,2,true);
  NFA_set_accepting(nfa,4,true);
  NFA_set_accepting(nfa,6,true);
  NFA_set_accepting(nfa,9,true);
  NFA_set_accepting(nfa,12,true);
  NFA_set_accepting(nfa,16,true);

  return nfa;
  
}
 


void DFA_repl(DFA dfa){
    printf("Running the %s dfa\n",DFA_get_description(dfa));
    bool answer = true;
    while(answer){
        char input[64];
        char thingForYn[64];
        printf("Enter a string to test!\n");
       
        scanf("%s",input);
        convert(input);
        printf("The dfa %s your input of '%s'\n", DFA_execute(dfa, input) ? "ACCEPTS" : "REJECTS", input);
        printf("Enter 'yes' to try again or 'no' to stop.\n");
        scanf( "%s",thingForYn);
        convert(thingForYn);
        answer = yesNo(thingForYn);
        
    }
    printf("That is it for the %s dfa.\n", DFA_get_description(dfa));
}

void NFA_repl(NFA nfa){
    printf("Running the %s nfa\n",NFA_get_description(nfa));
    bool answer = true;
    while(answer){
        char input[64];
        char thingForYn[64];
        printf("Enter a string to test!\n");
       
        scanf("%s",input);
        convert(input);
        printf("The nfa %s your input of '%s'\n", NFA_execute(nfa, input) ? "ACCEPTS" : "REJECTS", input);
        printf("Enter 'yes' to try again or 'no' to stop.\n");
        scanf( "%s",thingForYn);
        convert(thingForYn);
        answer = yesNo(thingForYn);
        
    }
    printf("That is it for the %s dfa.\n", NFA_get_description(nfa));

}

int main(int argc, char const *argv[]){
   /* printf("First testing the dfas.\n");
    DFA_repl(DFA_for_contains_abc());
    DFA_repl(DFA_for_dfa());
    DFA_repl(dfa_for_cat());*/
    DFA_repl(dfa_for_twos());
   //DFA_repl(dfa_for_binary());
    
   /// printf("\nNow testing the nfas.\n");
    ///NFA_repl(conference());
    ///NFA_repl(ends_in_ked());
    ///NFA_repl(contains_ath());

    printf("\n That's it!");
    

    return 0;
}
