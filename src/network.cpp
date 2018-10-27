#include "network.h"
#include "random.h"

void Network::resize(const size_t &n){
	RandomNumbers random;
	values.clear();
	values.resize(n);
	random.normal(values,0,1);
}


bool Network::add_link(const size_t &a, const size_t &b){

	
	//test
	std::cout<<"avant : "<<std::endl;
	for(auto it(links.begin());it!=links.end(); it++){
		std::cout<<it->first<<" :" << it->second <<std::endl;
	}

	if(a==b || b >=values.size() || a>= values.size()){
		return false;
	}else if(links.count(a) == 0 || links.count(b)==0){
		links.insert(std::make_pair(a,b));
		links.insert(std::make_pair(b,a));
	}else{
		auto iteq(links.equal_range(a));
		for(auto it(iteq.first); it != iteq.second; it++){
			if(it->second == b){
				return false;
			}
		}
		iteq=links.equal_range(b);
		for(auto it(iteq.first); it != iteq.second; it++){
			if(it->second == a){
				return false;
			}
		}
		links.insert(std::make_pair(a,b));
		links.insert(std::make_pair(b,a));
	}
	//test
	std::cout<<"apres : "<<std::endl;
	for(auto it(links.begin());it!=links.end(); it++){
		std::cout<<it->first<<" :" << it->second <<std::endl;
	}

	return true;	
}


size_t Network::random_connect(const double &a){
	return 0;
}

size_t Network::set_values(const std::vector<double> &v){
	size_t size=values.size();
	if(! values.empty()) values.clear();
	values=v;
	return size;
}

size_t Network::size() const{
	return values.size();
}

size_t Network::degree(const size_t &_n) const{
	return links.count(_n);
}

double Network::value(const size_t &_n) const{
	return values[_n-1];
}

std::vector<double> Network::sorted_values() const{
	std::vector<double> sorted(values);
	double biggest; 
	try{
		if(values.empty()) throw std::string("No nodes found (values empty");
		else{
			for(size_t i(0); i<values.size(); i++){
				for(size_t j(i); j<values.size(); j++){
					if(sorted[j]>sorted[i]){
						biggest = sorted[j];
						sorted[j]=sorted[i];
						sorted[i]=biggest;
					}
				}
			}
		}
	
	
	}catch(const std::string &e){
		std::cerr<<e;
	}
	return sorted;
}

std::vector<size_t> Network::neighbors(const size_t &a) const{
	
	try{
		if(links.empty()) throw std::string("No links found");
		if(values.empty()) throw std::string("No nodes found");
		if(a>=values.size()) throw std::out_of_range("Index a bigger than possible number of nodes");

		std::vector<size_t> _neighbors;

	if(links.count(a) != 0 && ! links.empty()){
		auto iteq(links.equal_range(a));

		for(auto it(iteq.first); it != iteq.second; it++){
			_neighbors.push_back(it->second);
		}
		
	}
	
	return _neighbors;
		
	}catch(const std::string &e){
		std::cerr<<e;
	}catch(const std::out_of_range &r){
		std::cerr<<r.what();
	}
}
