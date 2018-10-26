#include "network.h"
#include "random.h"

void Network::resize(const size_t &n){
	RandomNumbers random;
	values.clear();
	values.resize(n);
	random.normal(values,0,1);
}


bool Network::add_link(const size_t &a, const size_t &b){
	std::multimap<size_t, size_t>::iterator itlow(links.lower_bound(a));
	std::multimap<size_t, size_t>::iterator itup(links.upper_bound(a));
	if(a==b || b >=values.size() || a>= values.size()) return false;
	
	while(itlow!=itup){
		if(itlow->second == b) return false;
		std::cout<<"infini 1"<<std::endl;
	}
	
	itlow= links.lower_bound(b);
	itup=links.upper_bound(b);
	
	while(itlow!=itup){
		if(itlow->second == a) return false;
		std::cout<<"infini 2"<<std::endl;
	}
	
	links.insert(std::make_pair(a,b));
	links.insert(std::make_pair(b,a));

	return true;
	
}


size_t Network::random_connect(const double&){
	return 0;
}

size_t Network::set_values(const std::vector<double>&){
	return 0;
}

size_t Network::size() const{
	return values.size();
}

size_t Network::degree(const size_t &_n) const{
	return links.count(values[_n]);
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

std::vector<size_t> Network::neighbors(const size_t&) const{
	std::vector<size_t> a;
	a.push_back(1);
	return a;
}
