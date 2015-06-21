/*
 * Observer.h
 *
 *  Created on: 2013-9-3
 *      Author: walter_2
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <vector>
//#include "boost/weak_ptr.hpp"
//#include "boost/shared_ptr.hpp"
//#include <boost/ptr_container/ptr_container.hpp>

namespace wfan {

class ISubject;

class IObserver {
public:
    virtual ~IObserver() {};
    virtual void Update(ISubject* theChangedSubject) = 0;
protected:
    IObserver();
};

//typedef boost::shared_ptr<IObserver> IObserverPtr;
/*
*/
class ISubject {
public:
    virtual ~ISubject() {};
/*
*/
    virtual void Attach(IObserver* pObserver) = 0;
    virtual void Detach(IObserver* pObserver) = 0;
    virtual void Notify() = 0;
protected:
    ISubject();
//private:
//    list<Observer*> *_observers;
};

class CSubject: public ISubject
{
public:
    virtual void Attach(IObserver* pObserver);
    virtual void Detach(IObserver* pObserver) ;
    virtual void Notify();
private:
    //std::vector<boost::shared_ptr<IObserver> > m_observers;
    std::vector<IObserver*> m_observers;
};

} /* namespace wfan */
#endif /* OBSERVER_H_ */
