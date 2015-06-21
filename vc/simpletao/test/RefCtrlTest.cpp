#include <stdio.h>
#include <string.h>

class RefCtrlNode {
public:
	RefCtrlNode(size_t n=1):m_nSize(n) {
		m_buf = new char[n];
		m_nSize = n;

		m_count = new int;
		*m_count = 1;
		printf("count is %d\n", *m_count);
	}
	RefCtrlNode(RefCtrlNode& rhs)
		:m_buf(rhs.m_buf),
		m_nSize(rhs.m_nSize),
		m_count(rhs.m_count)
		{
		
		(*m_count) ++;
		printf("count is %d\n", *m_count);
	}

	RefCtrlNode& operator=(const RefCtrlNode& rhs) {
		if(m_buf == rhs.m_buf) {
			return *this;
		}

		(*m_count) --;
		if(*m_count == 0) {
			printf("%d bytes is deleted at %xd\n", m_nSize, m_buf);
			delete[] m_buf;
			delete m_count;
		}

		m_buf = rhs.m_buf;
		m_nSize = rhs.m_nSize;
		m_count = rhs.m_count;
		(*m_count) ++;
		return *this;
	}
	
	~RefCtrlNode() {
		(*m_count) --;
		printf("count is %d\n", *m_count);
		if(*m_count ==0) {
			printf("%d bytes is deleted at %xd\n", m_nSize, m_buf);
			delete[] m_buf;
			delete m_count;
		}
	}
	char *GetBuf() {
		return m_buf;
	}
private:
	char *m_buf;
	size_t m_nSize;
	int *m_count;

};

void RefCtrlTest() {
	printf("== Reference Control Test ==\n");
	RefCtrlNode a(10);
	char *p = a.GetBuf();

	strcpy(p, "hello");
	printf("a=%s\n", p);

	RefCtrlNode b = a;
	printf("b=%s\n",b.GetBuf());
	RefCtrlNode c(20);
	c = a;
	printf("c=%s\n",c.GetBuf());
}