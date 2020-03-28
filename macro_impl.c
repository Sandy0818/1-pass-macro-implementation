#include<stdio.h>
#include<conio.h>
#include<string.h>

//each structure variable stores 1 line of macro definition
struct mdt
{
    char lab[10];
    char opc[10];
    char oper[10];
} d[10];
 
void main()
{
	//variables to store input from files
    char label[10], opcode[10], operand[10], newlabel[10], newoperand[10];
    
	//to store name of macro
	char macroname[10];
    int i, lines;
    
    //pointers to files
    FILE *f1, *f2, *f3;
    
    f1 = fopen("macroin.txt", "r");
    f2 = fopen("macroout.txt", "w");
    f3 = fopen("mdt.txt", "w");
    
    //start reading input file
    fscanf(f1, "%s %s %s", label, opcode, operand);
 
 	//the assembly program should be read till its end - until we enounter END opcode.
    while(strcmp(opcode, "END") != 0)
    {
    	//if opcode read is MACRO then maro definition has been reached
        if(strcmp(opcode,"MACRO")==0)
        {
            strcpy(macroname, label);
            fscanf(f1, "%s %s %s", label, opcode, operand);
            lines = 0;
            
			//copy the macro definition into mdt file
			//MEND represents end of macro definition
            while(strcmp(opcode, "MEND") != 0)
            {
                fprintf(f3, "%s \t %s \t %s \n", label, opcode, operand);
                
                strcpy(d[lines].lab, label);
                strcpy(d[lines].opc, opcode);
                strcpy(d[lines].oper, operand);
                
				fscanf(f1,"%s %s %s", label, opcode, operand);
                lines++;
            }
        }
        
        //when the macro is being called by its name
        else if(strcmp(opcode, macroname) == 0)
        {
            printf("\n\nNumber of lines in macro definition = %d\n", lines);
            
            for(i = 0; i < lines; i++)
            {
            	//copy the macro definition instead of macro name into the output file
                fprintf(f2,"%s \t %s \t %s \n", d[i].lab, d[i].opc, d[i].oper);
                
				//display the same on console
                printf("\n DLAB = %s \n DOPC = %s \n DOPER = %s \n", d[i].lab, d[i].opc, d[i].oper);
            }
        }
        
        //if it's not a part of the macro definition, then copy the assembly program as it is into the output file
        else
        fprintf(f2, "%s \t %s \t %s \n", label, opcode, operand);
        
		fscanf(f1, "%s %s %s", label, opcode, operand);
    }
    
    
    fprintf(f2, "%s \t %s \t %s \n", label, opcode, operand);
    
    //close all file upon completion
    fclose(f1);
    fclose(f2);
    fclose(f3);
    
    printf("FINISHED");
    getch();
}
