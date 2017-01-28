#ifndef CPPBORROW_H
#define CPPBORROW_H
#include<utility>
#include<functional>
template<class A,bool own=true> struct box{
	box(){}
	box(const A& b):a(new A(b)){}
	box(A&& b):a(new A(std::move(b))){}
	~box(){delete a;}
	box<A,false> borrow()const{return box<A,false>(*a);}
	box<A,true> move(){box<A,true> b;b.a=a;a=0;return b;}
	box<A,true> copy()const{return box<A,true>(std::cref(*a));}
	A& operator*(){return *a;}
	A *a;
};
template<class A> struct box<A,false>{
	box(){}
	box(A& b):a(&b){}
	box<A,false> borrow()const{return box<A,false>(*a);}
	box<A,true> copy()const{return box<A,true>(std::cref(*a));}
	A& operator*(){return *a;}
	A *a;
};
#endif
