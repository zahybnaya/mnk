#include "dotexporter.h"
#include <string.h>
#include <sstream>

static void print_node(Node* n, std::ostream& out) ;
static void print_path(std::string p, Node* n, std::ostream& out); 

void todot(Node* n , std::ostream& out){
	out << " digraph g {" <<std::endl;
	print_path("", n, out);
	print_node(n, out) ;
	out << " }" <<std::endl;
}

static void print_node(Node* n, std::ostream& out) {
	std::string shape=n->player?"box":"circle";
	out<<"\"" << n << "\"" <<"[label=\""<<n->val/n->visits <<"\"" <<" shape="<<shape <<"];"<<std::endl;
	for (child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
		print_node(i->second, out);
	}
}
static void print_path(std::string p, Node* n, std::ostream& out) {
	std::stringstream ss;
	ss<< p << (p==""?"":" -> ") << "\"" << n << "\"" ;
	if(n->children.empty()) {
		out << ss.str() << std::endl;
	}
	for (child_map::const_iterator i = n->children.begin(); i != n->children.end(); ++i) {
		print_path(ss.str(), i->second, out);
	}
}
