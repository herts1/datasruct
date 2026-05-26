typedef int InfoType;  //其他数据项 


typedef int KeyType;   //定义关键字int 
typedef	struct {
	KeyType key;
	InfoType data;
}RecType;              //查找元素类型



//顺序查找

int SeqSearch(RecType R[],int n,KeyType k){
	int i=0;
	while(i<n&&R[i].key!=k){
		i++;
		if(i>=n){
			return 0;      //未找到 
		}else{
			return i+1;    //逻辑+1 
		}
	}
	
} 

int main () {
	return 0;
} 
//ACL（成功）=（n+1）/2 
