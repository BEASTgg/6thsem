## 1)  Write a YAAC Program to recognize nested IF control statements and display the levels of nesting

### Codes -

### Yaac -

```
%tokenIFRELOPSNUMBERID
 %{
 intcount=0;
 %}
 %%
 stmt:if_stmt{printf(“Noofnestedifstatements=%d\n”,count);exit(0);}
 ;
 if_stmt:IF‘(‘cond‘)’if_stmt{count++;}
 |S;
 ;
 cond:xRELOPx
;
 x:ID
 |NUMBER
 ;
 %%
 intyyerror(char*msg)
 {
 printf(“InvalidExpression\n”);
 exit(0);
 }
 main()
 {
 printf(“Enterthestatement”);
 yyparse();
 }
```

### Output -

```

```
