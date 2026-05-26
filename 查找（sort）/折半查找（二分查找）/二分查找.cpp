typedef int InfoType;  //其他数据项 


typedef int KeyType;   //定义关键字int 
typedef	struct {
	KeyType key;
	InfoType data;
}RecType;              //查找元素类型

//折半查找（二分查找）

int BinSearch(RecType R[],int n,KeyType k){
	int low=0,high=n-1,mid;
	while(low<=high){
		mid=(low+high)/2;
		if(k==R[mid].key){
			return mid+1;
		}else if(k<R[mid].key){
			high=mid-1;         
		}else{
			low=high+1;
		}
		
	}
	return 0;
} 

//ASL(bn)=log(2)[n+1]-1


int BinSerach2(RecType R[],int n,KeyType k){
	int low=0,high=n-1,mid;
	while(low<=high){
		mid=(low+high)/2;
		if(k<=R[mid].key){
			high=mid-1;
		}else{
			low=mid+1;
		}
		return high+1;
		
		
	}

}
int main() {
	return 0;
} 
