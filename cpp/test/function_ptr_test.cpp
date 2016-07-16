#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <execinfo.h>


typedef void** VPTR;
typedef void(*VoidFunc)(void);

const int TRACE_MSG_SIZE = 64;

typedef void (*HEX_DUMP_FN_PTR)(char *p, int s, FILE* fd);
// compile with -rdynamic during link, and -g without -O#
void stackdump(FILE* fd=stdout)
{
    void* trace[ TRACE_MSG_SIZE ];
    char** messages = NULL;
    int trace_size = 0;

    trace_size = backtrace( trace, 64 );
    messages = backtrace_symbols( trace, trace_size );
    fprintf(fd, "--- stack backtrace begin ---\n");
    for( int i = 0; i < trace_size; ++i )
    {
        fprintf(fd,"%s\n" , messages[i]);
    }

    fprintf(fd,"--- stack backtrace end ---\n");

    free (messages);
}

void hexdump(char *p, int s, FILE* fd=stderr) {     
	for (int i = 0; i < s; i++) {         
    	fprintf(fd, "%02x ", *(char *)(p+i));    
	}     
	fprintf(fd, "\n"); 
}

int statistic(const char* file, int line, FILE* fd=stderr) {
	
	static uint64_t total_count = 0;

	time_t timestamp = time(NULL);
	total_count ++; 

	fprintf(fd,"[statistic] %ld. %s:%d called %ld\n", timestamp, file, line, total_count);
	stackdump();
	return total_count;
}

class Point {
public:
	Point(double x):m_x(x) {}
	virtual ~Point() {}

	double x() const { return m_x; }
	virtual void dump() { printf("Point::dump x=%f\n", m_x); }
	virtual void move() { printf("Point::move point\n"); }
private:
	double m_x;

};

class Point2D:public Point {
public:  
	Point2D(double x, double y):Point(x), m_y(y) {}
	virtual ~Point2D() {}

	double y() const { return m_y; }
	virtual void dump() { printf("Point2D::dump x=%f, y=%f\n", x(), m_y); }
	virtual void move() { printf("Point2D::move point2d\n"); }
private:
private:
	double m_y;

};

class Printable
{
public:
	virtual int print() = 0;

};

class Shape {
public:
	Shape(): m_color(0) {}
	virtual ~Shape() {}
	int GetColor() {return m_color; };
	void SetColor(int color) { m_color = color; };
	virtual int draw() = 0;
	virtual void dump() { printf("Shape::dump: color=%d", m_color);}
private:
	int m_color;	
};

class Circle: public Shape {
public:
	Circle(double x, double y, double r): Shape(), m_center_x(x), m_center_y(y), m_radius(r) { SetColor(1);}
	virtual int draw() { printf("Circle::draw: circle , color=%d\n", GetColor()); return 0; }
	virtual void dump() { printf("Circle::dump: x=%f, y=%f, r=%f\n", m_center_x, m_center_y, m_radius);}
private:
	double m_center_x;
	double m_center_y;
	double m_radius;
};

class Line: public Shape, public Printable {
public:
	Line(double x1, double y1, double x2, double y2): Shape(),m_start_x(x1), m_start_y(y1), m_end_x(x2), m_end_y(y2) {SetColor(2);}
	virtual int draw() { printf("Line::draw: line, color=%d\n", GetColor()); return 0;}
	virtual void dump() { printf("Line::dump: x1=%f, y1=%f, x2=%f, y2=%f\n", m_start_x, m_start_y, m_end_x, m_end_y);}
	virtual int print() { printf("Line::print\n"); return 0;}
private:
	double m_start_x;
	double m_start_y;
	double m_end_x;
	double m_end_y;
};

typedef void (Point::*POING_DUMP_FN_PTR)();
typedef int  (Line::*LINE_DRAW_FN_PTR)();
typedef void (Line::*LINE_DUMP_FN_PTR)();
typedef int  (Line::*LINE_PRINT_FN_PTR)();

typedef int  (Printable::*PRINT_FN_PTR)();
typedef int  (Shape::*DRAW_FN_PTR)();

int test_address(int argc, char* argv[]) {

	int var = 1;
	int val = 2;
	int ptrSize = sizeof(void*);
	printf("pointer size=%d\n", ptrSize);
	printf("pointer addr--var:%p, val: %p\n", &var, &val);

	if(ptrSize == 4) {
		int espAddr = 0;
		asm("movl %%esp,%0" : "=r"(espAddr));
		printf("stack espAddr=%p\n", espAddr);
	}

	printf("1. var=%ld\n", var);

	asm ("movl %1, %%eax; movl %%eax, %0;"
     :"=r"(var)        /* output */
     :"r"(val)         /* input */
     :"%eax"         /* clobbered register */
     );
	printf("2. var=%ld\n", var);

	statistic(__FILE__, __LINE__);

	Line* pLine = new Line(20.0, 30.0, 40.0, 60.0);
	Printable* pPrinter = (Printable*)pLine;
	printf("pLine:%p, pPrinter: %p\n", pLine, pPrinter);
	delete pLine;
	//pPrinter = NULL;
	pLine = NULL;
	return 0;
}


int test_point(int argc, char* argv[]) {

	Point* pObj = new Point(30.0);

	VPTR pVirTab = (VPTR) pObj;
	void* pVirFunc = *(pVirTab + 1);

	printf("Point size=%d\n", sizeof(Point));
	printf("pObj(vptr)=%p\n", pVirTab);
	printf("pObj vptr func1=%p\n",pVirFunc);

	POING_DUMP_FN_PTR fnPtr = &Point::dump;
	printf("fnPtr=%p\n", fnPtr);
	(pObj->*fnPtr)();

	delete pObj;
    pObj = NULL;
	
	return 0;

}

int test_shape(int argc, char* argv[])
{

	int a = 0x12345678;
	hexdump((char *)&a, 4);

	//get the general function address, and call it
	HEX_DUMP_FN_PTR pHexDumpFn = &hexdump;
	printf("pHexDumpFn=%p\n", pHexDumpFn);
	pHexDumpFn((char *)&a, 4, stdout);

	Point* pPoint = new Point(100);
	Circle* pCircle = new Circle(20.0, 30.0, 10);
	Line* pLine = new Line(20.0, 30.0, 40.0, 60.0);

	printf("pointer size=%d, int type=%d, double type size=%lu\n",  sizeof(pCircle), sizeof(int), sizeof(double));

	printf("shape size=%lu, pointer is %p\n",  sizeof(Shape), (Shape*)pLine);

	printf("circle size=%lu, pointer is %p\n", sizeof(*pCircle), pCircle);
	pCircle->dump();
	

	printf("line size=%lu, pointer is %p\n",   sizeof(*pLine), pLine);
	pLine->dump();

	printf("Printable size=%lu, pointer is %p\n",  sizeof(Printable), (Printable*)pLine);

	//get the member function address and call it
	LINE_DRAW_FN_PTR pDrawFn = &Line::draw;
	(pLine->*pDrawFn)();

	LINE_DUMP_FN_PTR pDumpFn = &Line::dump;
	(pLine->*pDumpFn)();

	LINE_PRINT_FN_PTR pPrintFn = &Line::print;
	(pLine->*pPrintFn)();

	printf("Line::draw address=%p, Line::dump address=%p, Line::print address=%p\n", pDrawFn, pDumpFn, pPrintFn);

	DRAW_FN_PTR pDrawFn2 = &Shape::draw;
	PRINT_FN_PTR pPrintFn2 = &Printable::print;

	printf("Shape::draw address=%p\n", pDrawFn2);
	printf("Printable::print address=%p\n", pPrintFn2);

	delete pCircle;
	delete pLine;
	delete pPoint;
	statistic(__FILE__, __LINE__);
	return 0;
}

int main(int argc, char* argv[])
{
	int ret = test_address(argc, argv);
	ret = test_point(argc, argv);
	printf("test_point, ret=%d\n", ret);

	ret= test_shape(argc, argv);
	printf("test_shape, ret=%d\n", ret);

	
}
