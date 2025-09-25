#include<iostream>
using namespace std;
//单链表节点的定义
template <typename E> class Link {
private:
	static Link<E>* freelist;

public:
	E element;  //元素域
	Link* next; //指针域
	//构造函数
	Link(const E* elemval, Link* nextval = nullptr) { //"=NULL"表示没有写时默认为NULL     //List<E> a(10,&b)
		element = elemval;
		next = nextval;
	}

	Link(Link* nextval = nullptr) {
		next = nextval;
	}

	//自定义内存管理，对delete，new符号的重载
	void* operator new (size_t size) {
		if (freelist == NULL) return ::new Link; //::为作用域解析符，::new表示全域作用下系统自带的new，防止重载的new影响
		Link<E>* temp = freelist;              //分配freelist中空余的节点
		freelist = freelist->next;             //freelist的指针后移一位
		return temp;                           //返回分配的地址
	}

	void operator delete (void* ptr) {     //void*表示无类型指针
		((Link<E>*)ptr)->next = freelist;  //加括号表示强制转换指针类型，这行表示将释放的对象的next指针指向freelist表头
		freelist = (Link<E>*)ptr;          //将ptr的地址添加到freelist中
	}
};


template <typename E> class LStack : public Link<E> {
private:
	Link<E>* top;
	int size;

public:
	LStack(int sz) {
		top = NULL;
		size = 0;
	}

	~LStack() {
		clear();
	}

	void clear() {
		while (top != NULL) {
			Link<E>* temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}

	void push(const E& it) {
		top = new Link<E>(it, top);
		size++;
	}

	E pop() {
		E it = top->element;
		Link<E>* ltemp = top->next;
		delete top;
		top = ltemp;
		size--;
		return it;
	}

	const E& topValue() const {
		return top->element;
	}

	int length() const {
		return size;
	}
};

//用栈来实现河内塔问题
enum TOHop {DOMOVE, DOTOH};
class TOHopj {
public:
	TOHop op;
	int num;
	Pole start , goal, tmp;
	
	TOHopj(int n, Pole s, Pole g, Pole t){
		op = DOTOH; num = n;
		start = s; goal = g; tmp = t;
	}
	
	TOHopj(Pole s,Pole g){
		op = DOMOVE; start = s; goal = g; 
	}
};

void TOH(int n, Pole start, Pole goal, Pole tmp,
	Stack<TOHopj*>& S){
	S.push(new TOHopj(n,start,goal,tmp));
		TOHopj* t;
		while (S.length()>0){
			t = S.pop();
			if (t->op == DOMOVE)
				move(t->start, t->goal);
			else if (t->num > 0) {
				int num = t->num;
				Pole tmp = t->tmp;
				Pole goal = t->goal;
				Pole start = t->start;
				S.push(new TOHopj(num-1,tmp,goal,start));
				S.push(new TOHopj(start,goal));
				S.push(new TOHopj(num-1,start,tmp,goal));
			}
			delete t;
		}
}




