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

template <typename E> class LQueue :public Link<E>{
private:
	Link<E>* front;
	Link<E>* rear;
	int size;
	
public:
	LQueue(int size){
		front = rear = new Link<E>() ;size = 0;
	}
	
	~LQueue() {clear();delete front;}
	
	void clear(){
		while (front->next !=NULL){
			rear=front;
			front = front->next;
			delete rear;
		}
		rear = front;
		size = 0;
	}
	
	void enqueue(const E& it){
		rear->next = new Link<E>(it,NULL);
		rear = rear->next;
		size++;
	}
	
	E dequeue(){
		//Assert(size != 0,"Queue is empty")
		E it = front->next->element;
		Link<E>* ltemp = front->next;
		front->next = ltemp->next;
		if (rear == ltemp) rear = front;
		delete ltemp;
		size--;
		return it;
	}
	
	const E& frontValue() const {
		//Assert(size != 0,"Queue is empty);
		return front->next->element;
	}
	
	virtual int length() const {
		return size;
	}
};
