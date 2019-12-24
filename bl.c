#include <stdio.h>
//sudo apt-get install libblocksruntime-dev
//clang bl.c -fblocks -lBlocksRuntime -o bl
//clang bl.c --target=mips-linux-gnu -fblocks -lBlocksRuntime -o test
int reduce(int* balance,int balance_len,int(^fn)(int a,int b)){
    int index=0;
    int val=balance[0];
    for (int i = 1; i < balance_len; i++ )
    {
        val=fn(val,balance[i]);
        index++;
    }
    return val;
}
int * map(int* balance,int balance_len,int(^fn)(int a)){
    int * nbalance=malloc(sizeof(int)*balance_len);
    int index=0;
    int val=0;
    for (int i = 0; i < balance_len; i++ )
    {
        val=fn(balance[i]);
        nbalance[i]=val;
        index++;
    }
    return nbalance;
}
int* sorted(int *balance,int balance_len,int(^fn)(int a,int b)){
    int i = 0;
    int j = 0;
    int luaret=0;
    int sz=0; 
    int * arr=NULL;
    arr=malloc(sizeof(int)*balance_len);
    sz=balance_len;
    for (int i = 0; i < balance_len; i++ )
    {
       arr[i]=balance[i];
    }
    for(i=0;i<sz-1;i++){
        for(j=0;j<sz-i-1;j++){
            luaret=fn(arr[j],arr[j+1]);
            if (luaret>0){
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
    return arr;
}
int * filter(int* balance,int balance_len,int *nbalance_len,int(^fn)(int a)){
    int * nbalance=NULL;
    int * tmp=malloc(sizeof(int)*balance_len);
    int index=0;
    int val=0;
    for (int i = 0; i < balance_len; i++ )
    {
        val=fn(balance[i]);
        tmp[i]=val;
        if(val==1){
           index++;
        }
    }
    nbalance=malloc(sizeof(int)*index);
    index=0;
    for (int i = 0; i < balance_len; i++ )
    {
        val=tmp[i];
        if(val==1){
           nbalance[index]=balance[i];
           index++;
        }
    }
    free(tmp);
    *nbalance_len=index ;
    return nbalance;
}
int main() {
      int * nbalance=NULL;
   int nbalance_len=0;
   // void (^hello)(void) = ^(void) {printf("Hello, block!\n");};
   // hello();
   int(^cmpfunc)(int a,int b)=^(int a,int b){return a - b;};
   int values[] = { 1, 2, 3, 4, 5,6,7,8,9,10};
   //qsort(&values, 10, sizeof(int), cmpfunc);
   //int ret=cmpfunc(100,200);
   //int ret=reduce_all(&values, 10);
   //int(^myfn)(int a,int b)=^(int a,int b){return a + b;};
   //int ret=reduce_allc(&values, 10,myfn);
   int ret=reduce(&values,10,^(int a,int b){return a + b;});
   printf("retval: %d\n",ret);
   //nbalance=sorted(&values,10,^(int a,int b){return b-a;});
   nbalance=filter(&values,10,&nbalance_len,^(int a){return a>5;});
   printf("nbalance_len: %d\n",nbalance_len);
   for(int n = 0 ; n < nbalance_len; n++ ) {   
      printf("%d ", nbalance[n]);
   }
   printf("\nend: \n");
   return 0;
}
