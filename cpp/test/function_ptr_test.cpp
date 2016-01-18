#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>


typedef void (*HEX_DUMP_FN_PTR)(char *p, int s, FILE* fd);

void hexdump(char *p, int s, FILE* fd=stderr) {     
	for (int i = 0; i < s; i++) {         
    		fprintf(fd, "%02x ", *(char *)(p+i));    
	}     
	fprintf(fd, "\n"); 
}

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

typedef int  (Line::*LINE_DRAW_FN_PTR)();
typedef void (Line::*LINE_DUMP_FN_PTR)();
typedef int  (Line::*LINE_PRINT_FN_PTR)();

typedef int  (Printable::*PRINT_FN_PTR)();
typedef int  (Shape::*DRAW_FN_PTR)();

int main(int argc, char* argv[])
{
	int a = 0x12345678;
	hexdump((char *)&a, 4);

	//get the general function address, and call it
	HEX_DUMP_FN_PTR pHexDumpFn = &hexdump;
	pHexDumpFn((char *)&a, 4, stdout);

	Circle* pCircle = new Circle(20.0, 30.0, 10);
	Line* pLine = new Line(20.0, 30.0, 40.0, 60.0);

	printf("pointer size=%lu, int type=%lu, double type size=%lu\n",  sizeof(pCircle), sizeof(int), sizeof(double));

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

	return 0;
}
