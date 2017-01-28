# C++ Borrowing Class
Compile-time C++ borrowing mechanism like what's in Rust: Resources will be `borrow`ed, `move`ed, or `copy`ed instead of ambiguously "passed" everywhere. The mechanism will decide when to free resources. People might not like this since either `borrow`, `move` or `copy` have to be specified for any "passing". But this do makes sure everything will be "safe" at runtime.

# Usage

```
#include "borrow.hpp"

int main(){
	
	resource _a;	

	box<resource> a(_a);// To `borrow`, `move`, or `copy`, resource have to be wrapped like this.
						// Here, `a` seals resource from `_a`, which means generally `_a` can no longer be used anymore.
						// If `_a` have to be used, write `_a` as `std::cref(_a)` which will result in a deep copy.
						// It is recommended that all resources are wrapped in `box` to avoid C++ swap outside control of `box`.
						// By the way, C++17 might allow class template deduction which means `box a(_a)` will be legal
	
	*a;					// Access wrapped data using `operator*`

	{
		auto b=a.borrow()// `b` borrows resource from `a`. It shares resource with `a` but don't free that.
		*a.xxx()		// `a` is still able to access `b`
	}

	{
		auto b=a.move()	// `b` steals resource from `a`. If `a` borrowed resource from somebody else, a compiling
						// error will be given since `a` do not own the resource. Accessing `a` after this will throw
						// a runtime error. (There's no way to make this a compile time error since, this is C++)
						// Also, accessing empty-initialized box will also throw a runtime error. At least everything is
						// well defined.
	}

	{	
		auto b=a.copy()	// `b` owns a duplicate of resource inside `a`. They don't share the same memory space anymore.
	}
```
