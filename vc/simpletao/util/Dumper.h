#pragma once

#ifndef __CDUMP_H_
#define __CDUMP_H_

template<typename TC, typename TO>
class CDumper
{
public:
	CDumper(void);
	virtual ~CDumper(void);

	void dump(TC& container, TO& out);
};

template<typename TC, typename TO>
CDumper<TC, TO>::CDumper(void)
{
}

template<typename TC, typename TO>
CDumper<TC, TO>::~CDumper(void)
{
}

template<typename TC, typename TO>
void CDumper<TC, TO>::dump(TC& container, TO& out) {
	if(container.size() == 0){
		out<<"it's empty"<<"\n";
		return;
	}

	typename TC::const_iterator iter(container.begin());
	while(iter != container.end()) {
		out << *iter <<' ';
		++ iter;
	}


}
#endif