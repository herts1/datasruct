#define MSXI  1000
typedef int KeyType;

typedef struct {
	KeyType key;    //关键字类型 
	int link;
	
}IdxType;           //索引表元素类型

int IdxSearch(IdxType I[],int b,int R[],int n,KeyType k){
	int s=(n+b-1)/b;   //s:每块的元素个数
	int low=0,high=b-1,mid,i;
	while(low<high){
		mid=(low+high)/2;
		if(I[mid].key<k){
			high=mid-1;
		}else{
			low=mid+1;
		}
	} 
	i=I[high+1].link;
	while(i<=I[high+1].link+s-1&&R[i]!=k){
		i++;
	}
	if(i<=I[high+1].link+s-1){
		return i+1;
	}else{
		return 0;
	}
} 


 int main(){
 	return 0;
 }
 
 
 
 //ASL(blk)=log(2)[b+1]+s/2 
