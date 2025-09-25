template <typename E> class Stack{
private:
	void operator = (const Stack&){}
	Stack(const Stack&){}  //禁用拷贝与构造函数
	
public:
	Stack(){}
	virtual ~Stack(){}
	
	virtual void clear() = 0;
	
	virtual void push(const E& it) = 0;
	
	virtual E pop() = 0;
	
	virtual const E& topValue() const = 0;
	
	virtual int length() const = 0;
	
};

template <typename E> class AStack : public Stack<E>{
private:
	int maxSize;
	int top;
	E* listArray;
	
public:
	AStack(int size)
	{ maxSize = size ; top = 0; listArray = new E[size];}
	
	~AStack(){delete[]listArray;}
	
	void clear(){ top = 0; }
	
	void push(const E& it){
		listArray[top++]=it;  //先top+=1，再赋值
	}
	
	E pop(){
		return listArray[--top]; //先赋值，再top-=1
	}
	
	const E& topValue() const{
		return listArray[top-1];
	}
	
	int length() const { return top;}
	
	
};

