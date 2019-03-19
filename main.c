int singleparameter(int a)
{
    return a+a;
}

int multieparameter(int a, int b, int c, int d, int e, int f)
{
    return a+b+c+d+e+f;
}
void manyreturn(int a, int b, int *add, int *sub, int *mul, int *divi, int *square)
{
    *add = a+b ;
    *sub = a-b ;
    *mul = a*b ;
    *divi = a/b ;
    *square =a^b;
}
void reset_handler(void)
{
    int add, sub, mul, divi, square ;
    singleparameter(1);
    multieparameter(1, 2, 3, 4, 5, 6);
    manyreturn(1, 2, &add, &sub, &mul, &divi, &square);
    while (1)
		;
}
