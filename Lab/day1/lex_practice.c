#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define MAX 100

//  list of keywards
char *keywords[] = {"int", "float", "char", "double", "inclulde", "printf", 
                    "scanf", "while", "for"};
size_t num_of_Keywords = sizeof(keywords) / sizeof(keywords[0]);

// int main(){
//     printf("%zu\n", num_of_Keywords);
//     return 0;
// }

int iskeyword(char str[]){
    for(int i = 0; i<num_of_Keywords; i++){
        if(strcmp(str, keywords[i]) == 0){
            return 1; //if matched then returns 1
        }
    }
    return 0; //if not matched then return 0
}

// Main lexical analyzer
void lex(FILE *fp){
    char c;
    char token[MAX];
    int k = 0;
    while((c = fgetc(fp)) != EOF){
        //try to ignore white spaces
        if(isspace(c)) continue;
        
        //single line comment
        else if(c == '/'){
            k = 0;
            token[k++] = c;
            c = fgetc(fp);
            if( c == '/'){
                token[k++] = c;
                c = fgetc(fp);
                while(c != '\n' & k<MAX -1){
                    token[k++] = c;
                    c = fgetc(fp);
                }
                //1 line taken then ends the line using null terminator
                token[k] = '\0';
                printf("Token: %-20s \tType: singleLineComment\n", token);
            }
        }
        else if(c == '*'){
             k = 0;
            token[k++] = c;
            c = fgetc(fp);
            while(c != '*' & k<MAX -1){
                    token[k++] = c;
                    c = fgetc(fp);
                    if(c == '*'){
                        token[k++] = c;
                        c = fgetc(fp);
                        if(c == '/'){
                            token[k++] = c;
                            c = fgetc(fp);
                            token[k] = '\0';
                            break;
                        }
                    }
                }
                //multi line taken then ends the line using null terminator
                printf("Token: %-20s \tType: multilineLineComment\n", token);
            }
            else if(isalpha(c) || c == '_'){
                k = 0;
                token[k++] = c;
                while((isalnum(c = fgetc(fp))) || c== '_' & k < MAX -1){
                    token[k++] = c;
                }
                token[k] = '\0';
                if( c != EOF) ungetc(c, fp);
                
                if(iskeyword(token)){
                    printf("Token: %-20s \tType: Keyword\n", token);
                }else{
                    printf("Token: %-20s \tType: Identifier\n", token);
                }                
            }

            //number naki
            else if(isdigit(c)){
                
                 printf("Token: %-20s \tType: Number\n", token);
            }
        }
    }

int main(){
    FILE *fp = fopen("practice.c", "r");
    if(!fp){
        printf("File not found!\n");
        return 1;
    }

    printf("Lexical Analysis Output: \n\n");
    lex(fp);
    fclose(fp);
    return 0;
}