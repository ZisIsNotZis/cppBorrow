#ifndef CPPBORROW_H
#define CPPBORROW_H
#include<utility>
#include<functional>
template<class A,bool own=true> struct box{
	box(){}
	box(const A& b):a(new A(b)){}
	box(A& b):a(new A(std::move(b))){}
	box(A&& b):box(b){}
	box(A *b):a(b){}
	box(const box<A>& b):a(new A(b.a)){}
	box(box<A>& b):a(b.a){b.a=0;}
	box(box<A>&& b):box(b.a){}
	~box(){delete a;}
	box<A,false> borrow() const{return box<A,false>(*a);}
	box<A> move(){return box<A>(*this);}
	box<A> copy() const{return box<A>(std::cref(*a));}
	A& operator*(){return *a;}
	A *a;
};
template<class A> struct box<A,false>{
	box(){}
	box(A& b):a(&b){}
	box(A&& b):box(b){}
	box(A *b):a(b){}
	template<bool B> box(box<A,B>& b):a(b.a){}
	template<bool B> box(box<A,B>&& b):box(b){}
	box<A,false> borrow()const{return box<A,false>(*a);}
	box<A> copy()const{return box<A>(std::cref(*a));}
	A& operator*(){return *a;}
	A *a;
};
#endif
