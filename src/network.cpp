#include "network.h"
#include "random.h"

void Network::resize(const size_t &n){
	RandomNumbers random;
	values.clear();
	values.resize(n);
	random.normal(values,0,1);
}


bool Network::add_link(const size_t &a, const size_t &b){

	/*
	//test
	std::cout<<"avant : "<<std::endl;
	for(auto it(links.begin());it!=links.end(); it++){
		std::cout<<it->first<<" :" << it->second <<std::endl;
	}
	//
	*/
	try{
		if(b >=values.size() || a>= values.size()) throw std::out_of_range("In Network::add_link : Impossible de trouver les noeuds correspondants (index trop grand :)");
	}catch(std::out_of_range &r){
		std::cerr<<r.what()<<std::endl;
		return false;
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
	/*
	//test
	std::cout<<"apres : "<<std::endl;
	for(auto it(links.begin());it!=links.end(); it++){
		std::cout<<it->first<<" :" << it->second <<std::endl;
	}
	//
	*/
	return true;	
}


size_t Network::random_connect(const double &a){
	RandomNumbers random;
	size_t success(0);
	std::vector<int> degrees;

	degrees.resize(values.size());
	random.poisson(degrees,a);
	links.clear();

	for(size_t i(0); i<degrees.size(); i++){
		for(int j(0); j<degrees[i]; j++){
			this->add_link(i,random.uniform_double(0, values.size()-1) );
			success++;
		}
	}
	return success;
}

size_t Network::set_values(const std::vector<double> &v){
	size_t reset(0);
	try{
		if(v.empty()){
			throw std::string("In Network::set_values : No values to be set (please give a non empty vector)");
		}else{
			if(values.size()<=v.size()){
				for(size_t i(0);i<values.size(); i++){
				values[i]=v[i];
				reset++;
				}
			}
			else {
				for(size_t i(0);i<v.size(); i++){
				values[i]=v[i];
				reset++;
				}
			}
		}
	}catch(std::string &e){
			std::cerr<<e<<std::endl;
	}
	return reset;
}

size_t Network::size() const{
	return values.size();
}

size_t Network::degree(const size_t &_n) const{
	return links.count(_n);
}

double Network::value(const size_t &_n) const{
	return values[_n];
}

std::vector<double> Network::sorted_values() const{
	std::vector<double> sorted(values);
	try{
		if(values.empty()) throw std::string("In Network::sorted_values : No nodes found (values empty");
		else{
			std::sort(sorted.begin(), sorted.end());
			std::reverse(sorted.begin(), sorted.end());
		}
	}catch(const std::string &e){
		std::cerr<<e;
	}
	return sorted;
}

std::vector<size_t> Network::neighbors(const size_t &a) const{
	
	try{
		std::vector<size_t> _neighbors;
		if(links.empty()){ 
			throw std::string("In Network::neighbors : No links found");
		}else if(values.empty()){
			throw std::string("In Network::neighbors : No nodes found");
		}else if(a>=values.size()){
			throw std::out_of_range("In Network::neighbors : Index given bigger than possible number of nodes");
		}else if(links.count(a) != 0 && ! links.empty()){
		
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
