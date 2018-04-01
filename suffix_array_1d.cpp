#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>

template<typename T>
int suffix_array1D(std::vector<T> array, std::vector<T> sub_array){
	std::vector<std::tuple<std::vector<T>, int> > dir(array.size());

	auto iter = array.begin();
	for(int i = 0; i < array.size(); ++i){
		std::vector<T> _vec(array.size() - i);
		std::copy(iter++, array.end(), _vec.begin());
		dir[i] = std::make_tuple(_vec, i);
	}
	std::stable_sort(dir.begin(), dir.end());

	auto index = std::partition_point(dir.begin(), dir.end(), 
		[sub_array](auto e){return std::get<0>(e) < sub_array;});
	
	/* Output dir
	for(int i = 0; i < dir.size(); i++){
		for(int j = 0; j < std::get<0>(dir[i]).size(); j++){
			std::cout << std::get<0>(dir[i])[j];
		}
		std::cout << " " << std::get<1>(dir[i]) << std::endl;
	}
	*/
	return std::get<1>(*index);
}

int main(){
	std::vector<char> s{'6', '5', '4', '3', '2', '1'}, t{'3', '2'};
	int index = suffix_array1D<char>(s, t);
	std::cout << index << std::endl;
	return 0;
}

//this program needs g++, c++14?