int f()
{
    int x;
    x=1;
    while(x<5){
        int y = 1;
        while(y<5) {
            y=2;
            break;
            x++;
        }
        x++;
    }
    return x+y; // x=4 and y=2
}
