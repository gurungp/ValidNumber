//
//  main.cpp
//  state_machine_numberChecker
//
//  Created by Prashant Gurung on 18/10/2024.
//
#include <iostream>
#include <cstring>

enum FSM_States {
    START, // these value represents the start positions of each state entries
    AFTER_MINUS,
    AFTER_DOT,
  //  __VALID_END_STATES,
    SECOND_DIGIT_ONWARDS,
    MANTISSA,
    __LAST_STATE
};

struct FSM_STATE_INFO
{
    FSM_States state;
    char *tokens;
    FSM_States next_state;
};

#include <iostream>

int run(FSM_States start_state, FSM_STATE_INFO *state_machine,char* number)
{
    FSM_States current_state = start_state; // will be always START
    FSM_STATE_INFO* current_state_info = state_machine; // will always point to the first entry of the state machine
    char *num=number;
    bool found = false;
    std::string error = "";
    while(*num!=0)
    {
        
        while(current_state_info->state!=__LAST_STATE)
        {
        
               
            if(current_state_info->state==current_state) // current_state_info should point to the correct place in the array of states
            {
                // if the number character is in the valid tokens of current State tokens
                if(*num=='\0'){
                    break;
                }
                else if(strchr(current_state_info->tokens, *num)!=NULL) // if  match is found
                {
                    
                    current_state = current_state_info->next_state;
                    found = true;
                    //   break;
                    num++; // point to the next character
                }
                else
                {
                    current_state_info++;
                    found = false;
                    error = *num; // last found error character
                   // break;
                }
            }
            else
            {
                current_state_info++;
            }
            
             
        
        }
        
        if(*num==0)
            break;
        num++;
    }

    if( found && current_state>=SECOND_DIGIT_ONWARDS)
    {
     //   found = false;
        std::cout << "The number " << number << " is valid."<<  std::endl;
    }
    else{
        std::cout << "The number " << number << " is not valid. " << "Got a \'" << error << "\' in it." << std::endl;

    }

       
    
//    std::cout << "current_state " << current_state << " current_array_state " << current_state_info->state << ". final number was " << error << " Found : " << found <<  std::endl;
    
 
    
    return 0;
}

int main(int argc, const char * argv[]) {
    
    FSM_STATE_INFO state_machine[] =
    {
        {START,"0123456789",SECOND_DIGIT_ONWARDS},
        {START,"-",AFTER_MINUS},
        {AFTER_MINUS,"0123456789",SECOND_DIGIT_ONWARDS},
        {SECOND_DIGIT_ONWARDS,"0123456789",SECOND_DIGIT_ONWARDS},
        {SECOND_DIGIT_ONWARDS,".",AFTER_DOT},
        {AFTER_DOT,"0123456789",MANTISSA},
        {MANTISSA,"0123456789",MANTISSA},
        {__LAST_STATE,"",__LAST_STATE},
    };
    
    
//
//    FSM_STATE_INFO *entrytoMantissa = &state_machine[MANTISSA];
//    std::cout << "entrytoMantissa State value is " << entrytoMantissa->state << std::endl;
//    std::cout << "entrytoMantissa Tokens are " << entrytoMantissa->tokens << std::endl;
//    
//    FSM_STATE_INFO *entrytoAfterDot = state_machine+5; // After Dot is the 6th entry
//    std::cout << "entrytoAfterDot State value is " << entrytoAfterDot->state << std::endl;
//    std::cout << "entrytoAfterDot Tokens are " << entrytoAfterDot->tokens << std::endl;
    
    run(START, state_machine, "3.14");
    run(START, state_machine, "-7");
    run(START, state_machine, "-22.0");
    run(START, state_machine, "--22.0");
    run(START, state_machine, "-22.a0");
    run(START, state_machine, "-1.");
    run(START, state_machine, "--");
    run(START, state_machine, "-745756.456456-");
    run(START, state_machine, "-.");
    run(START, state_machine, "234-.");
    run(START, state_machine, "-234.42342");
//   
    return 0;
}
