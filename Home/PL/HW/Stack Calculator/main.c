#include "head.h"

int main(int argc, char *argv[]){
    Plate *plates = NULL;
    char c;
	int i,j,k, ans = 0;
    for (k=1; k < argc; k++){
        if (isnm(argv[k])){
            plates = push(plates, atoi(argv[k]));
        }
        else if (strlen(argv[k]) == 1 || !strcmp(argv[k], "*m")){
            if (len(plates)<2){
                printf("Not enough numbers");
                exit(2);
            }
            if (!strcmp(argv[k], "*m")) c = '*';
            else c = *argv[k];
            i = pop(&plates);
			j = pop(&plates);
			switch(c){
                case '+':
				    plates = push(plates, j + i);
				    break;
			    case '-':
				    plates = push(plates, j - i);
				    break;
			    case '*':
				    plates = push(plates, j * i);
				    break;
			    case '/':
				    plates = push(plates, j / i);
				    break;
                default:
                    printf("You wrote something wrong");
                    exit(3);
            }
        }
        else{ 
            printf("You wrote something wrong");
            exit(7);
        }
    }	
    if (len(plates)!=1){
        printf("Not enough operations");
        exit(4);
    }
	ans = pop(&plates);
	printf("Result of line is %d\n", ans);

    return 0;
}  
