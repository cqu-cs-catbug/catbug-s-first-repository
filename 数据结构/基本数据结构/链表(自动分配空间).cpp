#include<iostream>

//单链表节点的定义
template <typename E> class Link{
private:
	static Link<E>* freelist;
	
public:
	E element;  //元素域
	Link* next; //指针域
	//构造函数
	Link(const E* elemval,Link* nextval = nullptr){ //"=NULL"表示没有写时默认为NULL     //List<E> a(10,&b)
		element = elemval;  next = nextval;
	}
	
	Link(Link* nextval = nullptr){
		next = nextval;
	}
	
	//自定义内存管理，对delete，new符号的重载
	void* operator new(size_t size){
		if(freelist == NULL) return ::new Link;//::为作用域解析符，::new表示全域作用下系统自带的new，防止重载的new影响
		Link<E>* temp = freelist;              //分配freelist中空余的节点
		freelist = freelist->next;             //freelist的指针后移一位
		return temp;                           //返回分配的地址
	}
	
	void operator delete (void* ptr) {     //void*表示无类型指针
		((Link<E>*)ptr)->next = freelist;  //加括号表示强制转换指针类型，这行表示将释放的对象的next指针指向freelist表头
		freelist = (Link<E>*)ptr;          //将ptr的地址添加到freelist中
	}
}; 

template <typename E> 
Link<E>* Link<E>::freelist = NULL; //静态成员必须在类外提供一次定义
//Link<E>*表示类型是指向Link<E>的指针
//Link<E>::freelist表示freelsit是link<E>当中的全局变量

//链表的功能实现
template <typename E> class LList : public Link<E> {
private:
	Link<E>* head;
	Link<E>* tail;
	Link<E>* curr;
	int cnt;
	
	void init(){
		curr = tail = head = new Link<E>;
		cnt = 0;
	}
	
	void removeall(){
		while(head!=nullptr){
			curr = head;
			head = head->next;
			delete curr;
		}
	}
	
public:
	LList(int size){ init();} //初始化链表
	~LList() {removeall();}   //析构
	void print() const;
	void clear() { removeall(); init();}
	
	void insert(const E* it){
		curr -> next = new Link<E>(it, curr->next);
		if (tail==curr) tail = curr->next;
		cnt++;
	}
	
	void append(const E* it){
		tail = tail->next = new Link<E>(it,nullptr);
		cnt++;
	}
	
	E remove(){
		if(curr->next==nullptr){return;}
		E it = curr->next->element;
		Link<E>* ltemp = curr->next;
		if(tail == curr->next) tail = curr;
		curr->next = curr->next->next;
		delete ltemp;
		cnt--;
		return it;
	}
	
	void moveToStart(){  //指针置于末尾
		curr = head;
	}
	
	void moveToEnd(){ //指针置于开头
		curr = tail;
	}
	
	void prev(){  //指针前移一位
		if(curr==head){return;}
		Link<E>* temp = head;
		while(temp->next!=curr) temp=temp->next;
		curr = temp;
	}
	
	void next(){
		if(curr != tail ){curr = curr->next;}
	}
	
	int length() const { return cnt;}
	
	int currPos() const {
		Link<E>* temp = head;
		int i;
		for(int i=0;curr!=temp;i++){
			temp = temp->next;
			return i;
		}
	}
	
	void moveToPos(int pos){ //移到第pos位
		if(pos<0||pos>cnt) return ;
		curr = head;
		for(int i=0;i<pos;i++) curr = curr->next;
	}
	
	const E& getValue() const {
		if(curr->next == nullptr){return nullptr;}
		return curr->next->element;
	}
};
