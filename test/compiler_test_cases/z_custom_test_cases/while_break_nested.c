int f()
{
    int x;
    x=1;
    while(1){
        int y = 1;
        while(y<5) {
            y=2;
            break;
            x++;
        }
        x++;
        if(x==5 && y==2) {
            return 1234;
        }
    }
    return 0;
}
