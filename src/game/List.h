#ifndef __LIST_
#define __LIST_

#define SAFE_DELETE(a)				{if(a){delete (a);a=NULL;}}

enum SeekMode
{
	L_PRE	= 0x01,
	L_NEXT	= 0x02,
	L_START	= 0x04,
	L_LAST	= 0x08
};

enum InsertMode
{
	L_IPRE	= 0x01,
	L_INEXT	= 0x02,
};

//agent list 
template<class T>
class Stack
{
public:

	T*		data;
	int		size;
	int		count;

	//--------------------------------------------------------------------------------------
	Stack(int _stacksize)
	//--------------------------------------------------------------------------------------
	{
		count = -1;
		size = _stacksize;

		if(0 < size)
		{
			data = (T*)MALLOC(sizeof(T)*size);
		}				
	}


	//--------------------------------------------------------------------------------------
	~Stack()
	//--------------------------------------------------------------------------------------
	{
		SAFE_DELETE(data);
//		while(NULL != Pop()){}
	}

	//--------------------------------------------------------------------------------------
	void Push(T _data)
	//--------------------------------------------------------------------------------------
	{
		if(count+1 >= size)
		{
			return;
		}
		data[++count] = _data;
	}


	//--------------------------------------------------------------------------------------
	T Pop()
	//--------------------------------------------------------------------------------------
	{
		if(0 > count)	{return NULL;}
		return (data[count--]);
	}

	//--------------------------------------------------------------------------------------
	int GetStackCount()
	//--------------------------------------------------------------------------------------
	{
		return (count+1);
	}
};


#define		GetNodeCount(a)		((a)->count)	
#define		GetNow(a)		((a)->now)
#define		SetNow(a,b)		((a)->now = (b))	 
#define		GetData(a)		((a)->now->data)	
#define		MoveHead(a)		((a)->now = (a)->head)	
#define		MoveTail(a)		((a)->now = (a)->tail)	
#define		MovePre(a)		((a)->now = (a)->now->prev)	
#define		MoveNext(a)		((a)->now = (a)->now->next)	
#define		InitList(a)			((a)->now = (a)->head->next)	
//#define		GetNowNode(a)	((a)->now)	
//#define		GetTailNode(a)	((a)->tail)	
//#define		GetHeadNode(a)	((a)->head)	

#define		NotEndList(a)		((a)->now != (a)->tail)	

#define		DeleteNowList(a)	SAFE_DELETE((a)->now->data)


//agent list 
template<class T>
class List2
{
public:
	typedef struct Node
	{
		struct Node*	prev;
		struct Node*	next;
		T				data;
	};
	Node* head;
	Node* tail;
	Node* now;
	Node* saveNode;
	int count;

	//--------------------------------------------------------------------------------------
	List2()
	//--------------------------------------------------------------------------------------
	{
		head = GL_NEW Node;
		tail = GL_NEW Node;
		now = head;

		head->prev = head;
		head->next = tail;
		tail->prev = head;
		tail->next = tail;

//		count = 2;
	}

	//--------------------------------------------------------------------------------------
	~List2()
	//--------------------------------------------------------------------------------------
	{
		SAFE_DELETE(head);
		SAFE_DELETE(tail);
	}

	//--------------------------------------------------------------------------------------
	void Insert_prev(T nodeData)
	//--------------------------------------------------------------------------------------
	{
		if(now == head)
		{
			return;
		}

		Node* tmpNode = GL_NEW Node;
		tmpNode->data = nodeData;

		now->prev->next = tmpNode;
		tmpNode->prev = now->prev;
		now->prev = tmpNode;
		tmpNode->next = now;

		now = tmpNode;

		count++;
	}

	//--------------------------------------------------------------------------------------
	void Insert_next(T nodeData)
	//--------------------------------------------------------------------------------------
	{
		if(now == tail)
		{
			return;
		}

		Node* tmpNode = GL_NEW Node;
		tmpNode->data = nodeData;

		now->next->prev = tmpNode;
		tmpNode->next = now->next;
		now->next = tmpNode;
		tmpNode->prev = now;

		now = tmpNode;

		count++;
	}

	//--------------------------------------------------------------------------------------
	void Delete()
	//--------------------------------------------------------------------------------------
	{
		if(now == head || now == tail)
		{
			return;
		}

		Node* tmpNode = now->next;
		now->prev->next = now->next;
		now->next->prev = now->prev;
		SAFE_DELETE(now);
		now = tmpNode;

		count--;
	}


	//--------------------------------------------------------------------------------------
	void SaveCurrentState()
	//--------------------------------------------------------------------------------------
	{
		saveNode = now;
	}

	//--------------------------------------------------------------------------------------
	void RestoreCurrentState()
	//--------------------------------------------------------------------------------------
	{
		now = saveNode;
		saveNode = NULL;
	}

};





//agent list 
template<class T>
class List
{
public:
	typedef struct Node
	{
		struct Node* prenode;
		struct Node* nextnode;
		T*		dest;
	};

	Node* firstnode;
	Node* lastnode;
	Node* currentnode;	
	int nodecount;
	int delmode;

	Stack<Node*>	*pStackPool;

	//--------------------------------------------------------------------------------------
	List()
	//--------------------------------------------------------------------------------------
	{
		pStackPool = NULL;
		nodecount = 0;
		firstnode = NULL;
		lastnode = NULL;
		currentnode = NULL;
		delmode = 0;
	}

	//--------------------------------------------------------------------------------------
	List(int stackpoolsize)
	//--------------------------------------------------------------------------------------
	{
		nodecount = 0;
		firstnode = NULL;
		lastnode = NULL;
		currentnode = NULL;
		delmode = 0;

		pStackPool = GL_NEW Stack<Node*>(stackpoolsize);

		for(int loop = 0; loop < stackpoolsize; loop++)
		{
			pStackPool->Push( (Node*)MALLOC(sizeof(Node)));
		}
	}


	//--------------------------------------------------------------------------------------
	~List()
	//--------------------------------------------------------------------------------------
	{
		Node* tmpNode = NULL;
		if(pStackPool)
		{
			while(0 < pStackPool->GetStackCount())
			{
				tmpNode = pStackPool->Pop();
				SAFE_DELETE(tmpNode);
			}
		}
		SAFE_DELETE(pStackPool);
		DeleteAll();
	}

	//--------------------------------------------------------------------------------------
	void Insert(T* nodeData)
	//--------------------------------------------------------------------------------------
	{
		Insert(nodeData, L_INEXT);
	}

	//--------------------------------------------------------------------------------------
	void Insert(T* nodeData, int insertopt)
	//--------------------------------------------------------------------------------------
	{
		Node* tmpNode = NULL;
		if(pStackPool)
		{
			tmpNode = pStackPool->Pop();
		}
		else
		{
			tmpNode = GL_NEW Node;
		}

		tmpNode->prenode = NULL;
		tmpNode->nextnode = NULL;
		tmpNode->dest = nodeData;

		if(0 == nodecount)
		{
			firstnode = tmpNode;
			lastnode = tmpNode;
		}
		else
		{
			if(L_IPRE == insertopt)
			{
				tmpNode->prenode = currentnode->prenode;
				if(tmpNode->prenode)	{tmpNode->prenode->nextnode = tmpNode;}
				
				tmpNode->nextnode = currentnode;
				currentnode->prenode = tmpNode;
				
				if(firstnode == currentnode)	{firstnode = tmpNode;}
			}
			else	//if(L_INEXT == insertopt)
			{
				tmpNode->nextnode = currentnode->nextnode;
				if(tmpNode->nextnode)	{tmpNode->nextnode->prenode = tmpNode;}
				
				tmpNode->prenode = currentnode;
				currentnode->nextnode = tmpNode;
				
				if(lastnode == currentnode)	{lastnode = tmpNode;}
			}
		}

		currentnode = tmpNode;
		nodecount++;	
	}


	//--------------------------------------------------------------------------------------
	void Delete()
	//--------------------------------------------------------------------------------------
	{
		if(NULL == currentnode)	{return;}

		if(0 == delmode)
		{
			SAFE_DELETE(currentnode->dest);
		}
		
		nodecount--;

		if(0 == nodecount)
		{
			//SAFE_DELETE(currentnode);
			if(pStackPool)
			{
				currentnode->nextnode = NULL;
				currentnode->prenode = NULL;
				pStackPool->Push(currentnode);
				currentnode = NULL;
			}
			else				{SAFE_DELETE(currentnode);}

			firstnode = NULL;
			lastnode = NULL;
		}
		else if(firstnode == currentnode)
		{
			firstnode = currentnode->nextnode;
			firstnode->prenode = NULL;
			//SAFE_DELETE(currentnode);
			if(pStackPool)
			{
				currentnode->nextnode = NULL;
				currentnode->prenode = NULL;
				pStackPool->Push(currentnode);
				currentnode = NULL;
			}
			else				{SAFE_DELETE(currentnode);}
			currentnode = firstnode;
		}
		else if(lastnode == currentnode)
		{
			lastnode = currentnode->prenode;
			lastnode->nextnode = NULL;
			//SAFE_DELETE(currentnode);
			if(pStackPool)
			{
				currentnode->nextnode = NULL;
				currentnode->prenode = NULL;
				pStackPool->Push(currentnode);
				currentnode = NULL;
			}
			else				{SAFE_DELETE(currentnode);}
			currentnode = lastnode;
		}
		else
		{
			Node* tmpnode = currentnode->nextnode; 
			currentnode->prenode->nextnode = currentnode->nextnode;
			currentnode->nextnode->prenode = currentnode->prenode;
			//SAFE_DELETE(currentnode);
			if(pStackPool)
			{
				currentnode->nextnode = NULL;
				currentnode->prenode = NULL;
				pStackPool->Push(currentnode);
				currentnode = NULL;
			}
			else				{SAFE_DELETE(currentnode);}
			currentnode = tmpnode;
		}
	}


	//--------------------------------------------------------------------------------------
	T* CurNode()
	//--------------------------------------------------------------------------------------
	{
		if(currentnode)		{return (currentnode->dest);}
		return NULL;
	}


	//--------------------------------------------------------------------------------------
	bool Move(SeekMode _type)
	//--------------------------------------------------------------------------------------
	{
		switch(_type)
		{
			case L_PRE:		{if(currentnode->prenode)	{currentnode = currentnode->prenode;	return true;}	break;}
			case L_NEXT:	{if(currentnode->nextnode)	{currentnode = currentnode->nextnode;	return true;}	break;}
			case L_START:	{currentnode = firstnode;											return true;	break;}
			case L_LAST:	{currentnode = lastnode;											return true;	break;}
			default:		{break;}
		}

		return false;
	}

	//--------------------------------------------------------------------------------------
	int GetCount()
	//--------------------------------------------------------------------------------------
	{
		return nodecount;
	}


	//--------------------------------------------------------------------------------------
	bool IsLast()
	//--------------------------------------------------------------------------------------
	{
		if(currentnode == lastnode)	{return true;}
		return false;
	}


	//--------------------------------------------------------------------------------------
	void DeleteAll()
	//--------------------------------------------------------------------------------------
	{
		while(0 < nodecount)	{Delete();}
	}
};


#endif	//	__LIST_




