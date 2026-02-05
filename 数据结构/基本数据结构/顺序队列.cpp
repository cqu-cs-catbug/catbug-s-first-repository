template <typename E> class Queue{ //先进先出
private:
	void operator =(const Queue&){}
	Queue(const Queue&){}
public:
	Queue(){}
	virtual ~Queue(){}
	
	virtual clear() = 0;
	
	virtual void enqueue(const E&) = 0; //入队
	
	virtual E dequeue() = 0; //出队
	
	virtual const E& frontValue() const = 0; //拷贝前面一个值
	
	virtual int length() const = 0; //队中元素个数
};

template <typename E> class AQueue : public Queue<E>{ //顺序队列
private:
	int maxSize;
	int front;
	int rear;
	E* listArray;
	
public:
	AQueue(int size){
		maxSize = size + 1;
		rear = 0; front = 1;
		listArray = new E[maxSize];
	}
	
	~AQueue (){ delete[] listArray;}
	
	void clear(){ rear = 0; front = 1;}
	
	void enqueue (const E& it){ //入队
		//Assert (((rear+2) % maxSize) != front ,"Queue si full!")
		rear = (rear + 1) % maxSize;
		listArray[rear] = it;
	}
	
	E dequeue(){ //出队
		//Assert(length() != 0,"Queue is empty");
		E it = listArray[front];
		front = (front+1) % maxSize;
		return it;
	}
	
	const E& frontValue() const {
		//Assert(length() != 0,"Queue is empty");
		return listArray[front];
	}
	
	virtual int length() const {
		return ((rear+maxSize) - front + 1) % maxSize;
	}
	
};

