
#include <map>
#include <string>
#include <iostream>
#include "framework.h"
using namespace std;
namespace Prog4 {

	Pack::Pack(int fl = 0, std::string n = "MI", std::string a = "autor_mane", int t = 0) {
		if((fl!= 1)&&(fl!= 0))
			flag = 0;
			
		flag = fl;
		name = n;
		author_name = a;
		num_cviz = t;
	};
	void Pack::setName(std::string n) { name = n; };
	void Pack::setAutor(std::string a) { author_name = a; };
	void Pack::setFlag(int t) {
		if ((t != 1) && (t != 0))
			throw std::exception("1-have;0-haven't");
		flag = t;
	}
	void Pack::setNum(int t) {
		if (t < 0)
			throw std::exception(" number more that zero");
		num_cviz = t;

	};



	//int Pack::add_to_rep(map <std::string, shared_ptr<Pack>>& rep) {
	//	auto tmp = rep.find(name);
	//	if (tmp != rep.end()) {
	//		std::cout << "rep have file with name " << name;
	//		return 1;
	//	}
	//	else {


	//		std::vector<std::string> havename;


	//		if (this->getType() == PACK_SOFT) {

	//			auto t = std::make_shared<Pack_soft>(*this);/*
	//			auto control = std::static_pointer_cast<>(t);*/
	//			if (!agraph(t, havename)) {

	//				rep[name] = t;
	//			}
	//			else {
	//				std::cout << "this pack have circl" << std::endl;
	//				return 1;
	//			}
	//		}
	//		if (this->getType() == PACK_EMPTY) {
	//			auto t = std::make_shared<Empty_pack>(*this);
	//			rep[name] = t;
	//		}
	//		if (this->getType() == PACK_MI) {
	//			auto t = std::make_shared<Pack_MI>(*this);
	//			for (int i = 0; i < t->link.size(); i++) {
	//				auto tmpLink = std::make_shared<Pack_soft>(t->link[i]);
	//				auto control = std::static_pointer_cast<Pack_soft>(tmpLink);
	//				if (!agraph(control, havename)) {

	//					rep[name] = t;
	//				}

	//				else {
	//					std::cout << "this pack have circl" << std::endl;
	//					return 1;
	//				}

	//			}
	//			rep[name] = t;
	//		}
	//	}
	//	return 0;
	//};
	int Pack::agraph(std::shared_ptr<Pack_soft> control,Vector<std::string> havename){
		

		for (int i = 0; i < control->link.size(); i++) {
			for (int j = 0; j < havename.size(); i++)

				if (havename[j] == control->link[i]->getName()) {
					return 1;
				}
				else
					havename.push_back(control->link[i]->getName());

				auto tmp = std::static_pointer_cast<Pack_soft>(control->link[i]);
				if (agraph(tmp,havename))
					return 1;
		}
		return 0;
	}

	void Pack::output_into() {

		std::cout << this->getType() << " | " << name << " | " << this->getAutor() << " | " << this->getFlag();

		//if (this->getType() == PACK_MI) {


		//	auto t = std::make_shared<Pack_MI>(*this);
		//	auto tmp = std::static_pointer_cast<Pack_MI>(t);

		//	std::cout << " | " << tmp->getRelease();
		//	std::cout << " | " << tmp->getreleaselast();
		//	std::cout << " | ";
		//	for (int i = 0; i < tmp->link.size(); i++) {
		//		std::cout << tmp->link[i]->getName() << " ";
		//	}


		//}

		//if (this->getType() == PACK_SOFT) {
		//	auto t = std::make_shared<Pack_soft>(*this);
		//	auto tmp = std::static_pointer_cast<Pack_soft>(t);
		//	std::cout << " | " << tmp->getRelease();
		//	std::cout << " | " << tmp->getreleaselast();
		//	std::cout << " |";
		//	for (int i = 0; i < tmp->link.size(); i++) {
		//		std::cout << tmp->link[i]->getName() << " ";
		//	}
		//}
		//std::cout << endl;
	
		
		return ;
	};
	int Pack::delete_f_rep(std::map <std::string, std::shared_ptr<Pack>>& rep) {

		auto tmp = rep.find(name);
		if (tmp == rep.end()) {
			std::cout << "rep havn't file with name " << name;
			return 1;
		}
		else {
			flag = 0;

		}

		return 0;
	};
	void Not_empty_pack::update_pack() {
		if ((this->getFlag() == 1) &&(last_version < inst_version)){
			last_version++;
		}
	};

	void  Not_empty_pack::setRelease(int t) { inst_version = t; };

	void  Not_empty_pack::setReleaselast(int t) { last_version = t; };

	int Not_empty_pack::unification(std::map <std::string, std::shared_ptr<Pack>>& rep) {
		std::map <std::string, std::shared_ptr<Pack>> buf;
		for (auto it = rep.begin(); it != rep.end(); it++) {
			if (it->second->getType() != PACK_EMPTY) {
				auto tmp = std::static_pointer_cast<Not_empty_pack>(it->second);
				for (int i = 0; i < tmp->link.size(); i++) {/*
					buf[tmp->link[i]->getName()] = ;*/
					this->link.push_back(tmp->link[i]);
				}
			}
	

		}/*
		for (int i = 0; i < link.size(); i++) {

			buf[link[i]->getName()] = link[i];
		}
		std::vector<shared_ptr<Pack>>linknew;
		for (auto it = buf.begin(); it != buf.end(); it++) {

			linknew.push_back(it->second);
		}*/

		return 0;
	};

	Vector<std:: shared_ptr<Pack>> Pack_soft::separation(Vector<std::string >name, Vector<int> last_vertion) {
		Vector<shared_ptr<Pack>> sep;
		if (name.size() != last_vertion.size())
			return sep;
		for (int i = 0; i < last_vertion.size(); i++) {
			auto tmp = std::make_shared<Pack_soft>(*this);
			if (tmp->getFlag() == 1) {
				if (last_vertion[i] > this->getRelease())
					last_vertion[i] = this->getRelease();
			tmp->setReleaselast(last_vertion[i]);
			}
			else
				tmp->setReleaselast(0);
			tmp->setName(name[i]);
			
			sep.push_back(tmp);

		}
		return sep;
	};
}