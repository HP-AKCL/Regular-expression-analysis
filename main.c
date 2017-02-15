#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct pattern
{
        char c;
        int min;
        int max;
        int flag;
        struct pattern *next;
}pat;
pat *deal_argv1(char *);
int main(int argc,char* argv[])
{
        if( argv[1] == NULL )
        {
                printf("argument error\n");
                exit(0);
        }
        pat *p = deal_argv1(argv[1]);

        pat *next = p;

        while( next->next != NULL )
        {
                printf("char: %c min:%d max:%d\n",next->c,next->min,next->max);
                next = next->next;
        }
        return 0;
}
pat* deal_argv1(char *argv)
{
        int len = strlen(argv);
        int i = 0;
        char *p = (char*)malloc(len+1);
        pat *pa = (pat*)malloc(sizeof(pat));
        pat *next, *next1;
        memcpy(p,argv,len);
        if( NULL == p || pa == NULL )
        {
                printf("caanot malloc\n");
                exit(0);
        }
        next1 = pa;
        next = pa;
        next->flag = 0;
        next->next = NULL;
        while( i <= len )
        {
                next1->c = p[i++];
                switch( next1->c )
                {
                        case '?':
                                if( i == 1)
                                {
                                        printf("error\n");
                                        exit(0);
                                }
                                else if( next->flag == 1 )
                                {
                                        printf("error\n");
                                        exit(0);
                                }
                                else
                                {
                                        next->flag = 1;
                                        next->max++;
                                        free(next1);
                                }
                                break;
                        case '+':
                                if( i == 1)
                                {
                                        printf("data error\n");
                                        exit(0);
                                }
                                else if( next->flag == 1 )
                                {
                                        printf("error\n");
                                        exit(0);
                                }
                                else
                                {
                                        next->min++;
                                        next->max = len;
                                        next->flag = 1;
                                        free(next1);
                                }
                                break;
                        case '*':
                                if( i == 1 )
                                {
                                        next->min = 0;
                                        next->max = len;
                                        next->flag = 1;
                                }
                                else if( next->flag == 1 )
                                {
                                        printf("error\n");
                                        exit(0);
                                }
                                else
                                {
                                        next->max = len;
                                        next->flag = 1;
                                        free(next1);
                                }
                                break;
                        case '.':
                                if( i == 1 )
                                {
                                        next->flag = 2;
                                        next->min = 1;
                                        next->max = 1;
                                }
                                else if(next->flag == 1)
                                {
                                        printf("error\n");
                                        exit(0);
                                }
                                else
                                {
                                        next->min++;
                                        next->max++;
                                        next->flag = 2;
                                        free(next1);
                                }
                                break;
                        default:
                                if( i == 1)
                                {
                                        next->min = 1;
                                        next->max = 1;
                                }
                                else if( next1->c == next->c )
                                {
                                        next->min++;
                                        next->max++;
                                        next->flag = 2;
                                        free(next1);
                                }
                                else
                                {
                                        next->next = next1;
                                        next = next1;
                                        next->min = 1;
                                        next->max = 1;
                                        next->flag = 0;
                                }
                                break;
                }
                next1 = (pat*)malloc(sizeof(pat));
                if( next == NULL )
                {
                        printf("caanot malloc\n");
                        exit(0);
                }
                next1->c = '\0';
                next1->flag = 0;
                next1->next = NULL;
        }
        return pa;
}
