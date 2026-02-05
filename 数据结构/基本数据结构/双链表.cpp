#include<iostream>
//双链表节点的定义
template <typename E> class Link{
private:
	static Link<E>* freelist;
	
public:
	E element;
	Link* next;
	Link* prev;
	
	Link(const E& it,Link* prevp,Link* nextp){
		element = it;
		prev = prevp;
		next = nextp;
	}
	Link(Link* prevp =NULL, Link* nextp =NULL){
		prev = prevp;
		next = nextp;
	}
	void* operator new(size_t size){
		if(freelist == NULL) return ::new Link;
		Link<E>* temp = freelist;
		freelist=freelist->next;
		return temp;
	}
	
	void operator delete(void* ptr){
		((Link<E>*)ptr)->next = freelist;
		freelist = (Link<E>*)ptr;
	}
};

template <typename E>
Link<E>* Link<E>::freelist = NULL;

template <typename E> 
class doubleLink : public Link<E>{
private:
	Link<E>* head;
	Link<E>* tail;
	Link<E>* curr;
	int cnt;
	
	void init(){
		curr = head = tail = new Link<E>;
		cnt = 0;
	}
	
	void removeAll(){
		while(head !=nullptr){
			curr = head;
			head->next;
			delete curr;
		}
	}
	
public:
	doubleLink(int size){
		init();
	}
	~doubleLink(){
		removeAll();
	}
	
	void clear(){
		removeAll();
		init();
	}
	
	void insert(const E& it){  //下面三个函数与单链表不同
		curr->next = curr->next->prev = 
		    new Link<E>(it,curr,curr->next);
		cnt++;
	}
	
	void append(const E& it){
		tail->prev = tail->prev->next = 
		    new Link<E> (it,tail->prev,tail);
	}
	
	E remove() {  
		if (curr->next == tail) return NULL;
		E it = curr->next->element;
		Link<E>* ltemp = curr->next;
		curr->next->next->prev = curr;
		curr->next = curr->next->next;
		delete ltemp;
		cnt--;
		return it;
	}
	
	void prev(){
		if(curr != head) curr = curr->prev;
	}
	
	void next(){
		if(curr != tail )curr = curr->next;
	}
	
	void moveToStart(){  //指针置于末尾
		curr = head;
	}
	
	void moveToEnd(){ //指针置于开头
		curr = tail;
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

