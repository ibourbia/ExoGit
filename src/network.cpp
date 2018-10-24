#include "network.h"

void Network::resize(const size_t &n){
	values.resize(n);
}


bool Network::add_link(const size_t&, const size_t&){
	return false;
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
	return 0;
}

double Network::value(const size_t &_n) const{
	return values[_n-1];
}

std::vector<double> Network::sorted_values() const{
	return values;
}

std::vector<size_t> Network::neighbors(const size_t&) const{
	
}
