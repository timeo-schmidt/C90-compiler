int g()
{
    int x = 0;
    int t = 500;
    switch(t)
    {
        case 0:
            x=5;
            break;
        case 500:
            x=2;
        case 99:
            x=x+1;
            break;
        default:
            x=t+1;

    }
    return x;
}
