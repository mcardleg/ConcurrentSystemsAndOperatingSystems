#define NUM_FROGS 4

//Declare globals
byte empty_pos;
byte frog[NUM_FROGS + 1]; //+1 in order to ignore frogs[0]
                           //so that array position can correspond to frog number
    
proctype lFrog(byte frog_num){
    byte from;
    byte to;
    printf( "START FROG %d AT %d GOING LEFT\n", frog_num, frog[frog_num]);
    do
    :: atomic{((frog[frog_num]-1)>0 && (frog[frog_num]-1)==empty_pos) -> 
    		from = frog[frog_num];
    		to = from - 1;
    		empty_pos = from;
    		frog[frog_num] = to;
    		printf( "MOVE FROG%d FROM %d TO %d\n", frog_num, from, to);
    		printf( "EMPTY %d, FROG1@%d, FROG2@%d, FROG3@%d, FROG4@%d\n", empty_pos, frog[1], frog[2], frog[3], frog[4]);
    		if
    		:: (frog[1]==5 && empty_pos==4) -> printf( "DONE!\n" ); assert(false);
    		:: else -> skip;
    		fi
    	}   
    :: atomic{((frog[frog_num]-2)>0 && (frog[frog_num]-2)==empty_pos) -> 
    		from = frog[frog_num];
    		to = from - 2;
    		empty_pos = from;
    		frog[frog_num] = to;
    		printf( "MOVE FROG%d FROM %d TO %d\n", frog_num, from, to);
    		printf( "EMPTY %d, FROG1@%d, FROG2@%d, FROG3@%d, FROG4@%d\n", empty_pos, frog[1], frog[2], frog[3], frog[4]);
    		if
    		:: (frog[1]==5 && empty_pos==4) -> printf( "DONE!\n" ); assert(false);
    		:: else -> skip;
    		fi
    	}   
    od;
}    

proctype rFrog(byte frog_num){
    byte from;
    byte to;
    printf( "START FROG %d AT %d GOING RIGHT\n", frog_num, frog[frog_num]);
    do
    :: atomic{((frog[frog_num]+1)<=5 && (frog[frog_num]+1)==empty_pos) -> 
    		from = frog[frog_num];
    		to = from + 1;
    		empty_pos = from;
    		frog[frog_num] = to;
    		printf( "MOVE FROG%d FROM %d TO %d\n", frog_num, from, to);
    		printf( "EMPTY %d, FROG1@%d, FROG2@%d, FROG3@%d, FROG4@%d\n", empty_pos, frog[1], frog[2], frog[3], frog[4]);
    		if
    		:: (frog[1]==5 && empty_pos==4) -> printf( "DONE!\n" ); assert(false);
    		:: else -> skip;
    		fi
    	}   
    :: atomic{((frog[frog_num]+2)<=5 && (frog[frog_num]+2)==empty_pos) -> 
    		from = frog[frog_num];
    		to = from + 2;
    		empty_pos = from;
    		frog[frog_num] = to;
    		printf( "MOVE FROG%d FROM %d TO %d\n", frog_num, from, to);
    		printf( "EMPTY %d, FROG1@%d, FROG2@%d, FROG3@%d, FROG4@%d\n", empty_pos, frog[1], frog[2], frog[3], frog[4]);
    		if
    		:: (frog[1]==5 && empty_pos==4) -> printf( "DONE!\n" ); assert(false);
    		:: else -> skip;
    		fi
    	}   
    od;
}
                           
init{
//set up where each frog is
    empty_pos = 2;
    frog[1] = 1;
    frog[2] = 3;
    frog[3] = 4;
    frog[4] = 5;
    printf( "EMPTY %d, FROG1@%d, FROG2@%d, FROG3@%d, FROG4@%d\n", empty_pos, frog[1], frog[2], frog[3], frog[4]);

//call each frog
    run rFrog(1);     //frog 1 goes right
    run lFrog(2);     //frog 2 goes left
    run lFrog(3);     //frog 3 goes left
    run lFrog(4);     //frog 4 goes left
}
