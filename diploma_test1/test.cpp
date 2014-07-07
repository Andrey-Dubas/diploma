

#include <initializer_list>
#include <iostream>
#include <algorithm>

int main(){
	auto l = {1, 2, 3, 4, 5};

	std::cout << "method size: " << l.size() << std::endl;

	int ret = 0;

	std::for_each(l.begin(), l.end(), [&ret](int ) { ++ret;} );

	std::cout << "lambda val: " << ret << std::endl;

	
}
