#ifndef CPPBORROW_H
#define CPPBORROW_H
#include<utility>
#include<functional>
template<class A,bool own=true> struct box{
	constexpr box(){}
	constexpr box(const A& b):a(new A(b)){}
	constexpr box(A& b):a(new A(std::move(b))){}
	constexpr box(A&& b):box(b){}
	constexpr box(A *b):a(b){}
	constexpr box(const box<A>& b):a(new A(b.a)){}
	constexpr box(box<A>& b):a(b.a){b.a=nullptr;}
	constexpr box(box<A>&& b):box(b.a){}
	~box(){delete a;}
	constexpr box<A,false> borrow() const{return box<A,false>(*a);}
	constexpr box<A> move(){return box<A>(*this);}
	constexpr box<A> copy() const{return box<A>(std::cref(*a));}
	constexpr A& operator*(){return *a;}
	constexpr A* operator->(){return a;}
	protected: 
		A *a;
};
template<class A> struct box<A,false>{
	constexpr box(){}
	constexpr box(A& b):a(&b){}
	constexpr box(A&& b):box(b){}
	constexpr box(A *b):a(b){}
	template<bool B> constexpr box(box<A,B>& b):a(b.a){}
	template<bool B> constexpr box(box<A,B>&& b):box(b){}
	box<A,false> constexpr borrow()const{return box<A,false>(*a);}
	box<A> constexpr copy()const{return box<A>(std::cref(*a));}
	A& operator*(){return *a;}
	//A* operator->(){return a;}
	protected: 
		A *a;
};
#endif
