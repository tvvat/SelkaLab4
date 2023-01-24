#include <map>
#include <string>
#include <iostream>
#include "manager.h"
using namespace std;
namespace Prog4 {

	bool Manager::auto_inst_file(int def, string name, int flag, string author, int release, int release_last, Vector<string> incl) {


		if (def == PACK_MI) {
			shared_ptr<Pack_MI> tmp = make_shared<Pack_MI>();

			tmp->setName(name);
			tmp->setFlag(flag);
			tmp->setAutor(author);
			tmp->setRelease(release);
			if (flag == 0)
				release_last = 0;
			tmp->setReleaselast(release_last);

			for (auto i = 0; i != incl.size(); i++) {
				int CHEAK = instlibforMI(incl[i], flag);
				if (!CHEAK) {
					tmp->setFlag(0);
					release_last = 0;
					tmp->setReleaselast(release_last);
					//добавить чистку не используемых пакетов
					cleaning();
				}
				else
					if (CHEAK != -1) {

						auto tmp_find = Mypack.find(incl[i]);
						tmp->link.push_back(tmp_find->second);
					}
					else
						return;
			}

			Mypack[name] = tmp;
		}

		if (def == PACK_EMPTY) {

			/*std::cout << "u can't creat this pack" << std::endl;*/
			shared_ptr<Empty_pack > tmp = make_shared<Empty_pack>();
			tmp->setName(name);
			tmp->setFlag(0);
			tmp->setAutor(author);
			std::cout << "set with flag 0(dont instal)" << std::endl;

			Mypack[name] = tmp;
		}

		if (def == PACK_SOFT) {
			shared_ptr<Pack_soft> tmp = make_shared<Pack_soft>();

			tmp->setName(name);
			tmp->setFlag(flag);
			tmp->setAutor(author);
			tmp->setRelease(release);
			tmp->setReleaselast(release_last);


			for (auto i = 0; i != incl.size(); i++) {
				auto tmp_find = Mypack.find(incl[i]);
				if (tmp_find != Mypack.end()) {
					if ((tmp_find->second->getType() == PACK_SOFT) ) {
						std::cout << "pack SOFT cant unclude pack SOFT or Empty" << std::endl;;
						tmp->setFlag(0);
						release_last = 0;
						tmp->setReleaselast(release_last);
					}
					else {
						if (tmp->getFlag() == 1) {
							tmp_find->second->setFlag(1);
							auto tm = std::static_pointer_cast<Not_empty_pack>(tmp_find->second);
							tm->setReleaselast(tm->getRelease());
						}
						tmp->link.push_back(tmp_find->second);
					}
				}
				else {
					std::cout << "havnt pack :" << incl[i] << "\nat the begining include this pack" << std::endl;

					tmp->setFlag(0);
					release_last = 0;
					tmp->setReleaselast(release_last);
					return;
				}
			}
			if (!check(name)) {
				tmp->setFlag(0);
				release_last = 0;
				tmp->setReleaselast(release_last);
				std::cout << "this lib nothing using" << std::endl;
			}
			Mypack[name] = tmp;
		}



		return 0;

	}



	int Manager::instlibforMI(std::string incl,int flag) {


			auto tmp_find = Mypack.find(incl);

			if (tmp_find != Mypack.end()) {
				if ((tmp_find->second->getType() == PACK_MI)) {
					std::cout << "pack MI cant unclude pack MI or Empty";


					return 0;
				}
				else {
					if (flag) {
						tmp_find->second->setFlag(1);
						auto tmp = std::static_pointer_cast<Not_empty_pack> (tmp_find->second);
						tmp->setReleaselast(tmp->getRelease());
					}
					return 1;
				}
			}
			else {
				std::cout << "havnt pack :" << incl << "\nat the begining include this pack" << std::endl; \
					return 0;
			}
		
		return -1;



	}
	bool Manager::check(std::string name) {
		bool flag = 0;
		for (auto it = Mypack.begin(); it != Mypack.end(); it++) {
			if (it->second->getType() == PACK_MI) {
				auto tmpMI = std::static_pointer_cast<Pack_MI>(it->second);
				auto t = tmpMI->link;
				for (int i = 0; i < t.size(); i++) {
					if (t[i]->getName() == name) {
						if (tmpMI->getFlag() == 0) {
							flag = 0;
						}
						else {
							flag = 1;
						}
					}

				}
			}

		}
		return flag;
	}

	bool Manager::cleaning() {

		for (auto it = Mypack.begin(); it != Mypack.end(); it++) {
			if (it->second->getType() == PACK_SOFT) {
				if (!check(it->second->getName())) {
					it->second->setFlag(0);
					auto tmps = std::static_pointer_cast<Pack_soft>(it->second);


					tmps->setReleaselast(0);

				};
			}

		}

		return 0;
	}
	bool Manager::unification(string in, Vector<string> all) {
		map< std::string, shared_ptr<Pack>>All;
		for (auto i = 0; i < all.size(); i++) {
			auto tmp = Mypack.find(all[i]);
			if (tmp == Mypack.end())
				return 1;
			else
				All[tmp->first] = tmp->second;
		}

		auto tmp = Mypack.find(in);
		if (tmp == Mypack.end())
			return 1;
		else {
			if (tmp->second->getType() == PACK_EMPTY)
				return 1;
			auto t = std::static_pointer_cast<Not_empty_pack>(tmp->second);
			t->unification(All);
		}
		return 0;
	}
	bool Manager::separation(string in, Vector<string> name, Vector<int> vertion) {
		auto t = Mypack.find(in);
		if (t == Mypack.end())
			return 1;
		for (int i = 0; i < name.size(); i++){	
			t = Mypack.find(name[i]);
			if (t != Mypack.end())
				return 1;
		}
		t = Mypack.find(in);
		if (t->second->getType() != PACK_SOFT)
			return 1;
		else{
			auto tmp = std::static_pointer_cast<Pack_soft>(t->second);
			auto New = tmp->separation(name,vertion);
			for (int i = 0; i < New.size(); i++) {
				Mypack[New[i]->getName()] = New[i];
			}
		}

		return 0;

	}
	bool Manager::show(std::ostream & os) {
	/*	os << "type  | name | install author |   |  Max release | Now release |count| include_pack";*/
		os << endl;

		for (auto it = Mypack.begin(); it != Mypack.end(); it++) {

			os << it->second->getType() << "  " << it->first << "  "  << it->second->getFlag()<< "  " << it->second->getAutor();

			if (it->second->getType() == PACK_MI) { 

				auto tmp = std::static_pointer_cast<Pack_MI>(it->second);

				os << "  "  <<  tmp->getRelease();
				os << "  "  <<  tmp->getreleaselast();
				os << "  ";
				os << tmp->link.size() << " ";
				for (int i = 0; i < tmp->link.size(); i++) {
						os << tmp->link[i]->getName() << " ";
				}
			}
				
			if(it->second->getType() == PACK_SOFT) {
				
				auto tmp = std:: static_pointer_cast<Pack_soft>(it->second);
				os << "  " << tmp->getRelease();
				os << "  " << tmp->getreleaselast();
				os << " ";
				os << tmp->link.size() << " ";
				for (int i = 0; i < tmp->link.size(); i++) {
					os << tmp->link[i]->getName()<< " ";
				}
			}
			if (it->second->getType() == PACK_EMPTY) {
				os << "  " << 0;
				os << "  " << 0;
				os << "  ";
				os << 0 << " ";

			}
			os << endl;
		}

		return 1;
	}
	bool  Manager::auto_inst(std::string  name) {

		auto tmp = Mypack.find(name);
		if (tmp == Mypack.end()) {
			return 1;
		}
		else {
			if (tmp->second->getType() == PACK_EMPTY) {
				tmp->second->setFlag(1);
			}
			else {
				auto t = std::static_pointer_cast<Not_empty_pack>(tmp->second);
				t->setFlag(1);
				t->setReleaselast(t->getRelease());
				setflag1auto(t);
			}

		}
		
		return 0;

	}

	int Manager::setflag1auto(std::shared_ptr<Not_empty_pack> control) {

		
		for (int i = 0; i < control->link.size(); i++) {
			

			control->link[i]->setFlag(1);
			control->setReleaselast(control->getRelease());
			auto tmp = std::static_pointer_cast<Not_empty_pack>(control->link[i]);
			setflag1auto(tmp);
			
		}
		return 0;
	}


	bool  Manager::ask_inst(std::string  name) {

		auto tmp = Mypack.find(name);
		if (tmp == Mypack.end()) {
			return 1;
		}
		else {
			if (tmp->second->getType() == PACK_EMPTY) {
				tmp->second->setFlag(1);
			}
			else {


				auto t = std::static_pointer_cast<Not_empty_pack>(tmp->second);

				if (setflag1ask(t)) {
					t->setFlag(0);
					t->setReleaselast(0);
					std::cout << "havnt soft for" << t->getName() << ",dont install this pack" << std::endl;
				}
				else {
					t->setFlag(1);
					t->setReleaselast(t->getRelease());
				}
			}

		}
		return 0;

	}

	int Manager::setflag1ask(std::shared_ptr<Not_empty_pack> control) {


		for (int i = 0; i < control->link.size(); i++) {

			std::cout << "install pack:" << control->link[i]->getName() << "(y/n)" << std::endl;
			char answ;
			std::cin >> answ;
					auto tmp = std::static_pointer_cast<Not_empty_pack>(control->link[i]);
			if (answ == 'n'){
				tmp->setFlag(0);
				tmp->setReleaselast(0);
				return 1;
			}
			else
				if (answ == 'y') {
					tmp->setFlag(1);
					tmp->setReleaselast(tmp->getRelease());
					
					if (setflag1ask(tmp))
						return 1;
				}
			

		}
		return 0;
	
	}

	/*flag = 1 автоматическое удаление*/
	bool Manager::delete_pack(std::string name,int flag) {

		auto tmp = Mypack.find(name);
		if (tmp == Mypack.end()) {
			return 1;
		}
		else 
			if (tmp->second->getType() == PACK_EMPTY) {
				tmp->second->setFlag(0);
			}
			else {
				auto t = std::static_pointer_cast<Not_empty_pack>(tmp->second);

				if (!checkmum(t->getName())) {
					t->setFlag(0);
					t->setReleaselast(0);
				}
				else
				{
					std::cout << "this file used some prog first delete prog\n";
				}

				if (flag)
					delet_rec(t);
				else
					delet_rec_ask(t);

			}
		return 0;
	};

	int Manager::delet_rec(std::shared_ptr<Not_empty_pack> control) {

		for (int i = 0; i < control->link.size(); i++) {


			auto tmp = std::static_pointer_cast<Not_empty_pack>(control->link[i]);
			
			delet_rec(tmp);
			if (!checkmum(tmp->getName())) {
				tmp->setFlag(0);
				tmp->setReleaselast(0);

			}
		}
		return 0;


	}
	int Manager::delet_rec_ask(std::shared_ptr<Not_empty_pack> control) {

		for (int i = 0; i < control->link.size(); i++) {


			auto tmp = std::static_pointer_cast<Not_empty_pack>(control->link[i]);
			
			delet_rec_ask(tmp);
			if (!checkmum(tmp->getName())) {
				std::cout << "delete pack  " << control->link[i]->getName() << "?(y/n)" << std::endl;
				char answ;
				std::cin >> answ;
				if (answ == 'y') {
					tmp->setFlag(0);
					tmp->setReleaselast(0);
				}
				
			}
		}
		return 0;


	}

	int Manager::checkmum(std::string name) {
	
	
		
		for (auto it = Mypack.begin(); it != Mypack.end(); it++) {
			if (it->second->getType() != PACK_EMPTY) {
				auto tmp = std::static_pointer_cast<Not_empty_pack>(it->second);
				auto t = tmp->link;
				for (int i = 0; i < t.size(); i++) {
					if (t[i]->getName() == name)
						if(tmp->getFlag() == 1)
						return 1;

				}
			}

		}
		return 0;
	};

	void Manager::glob_update(std::ostream & os) {
		for (auto it = Mypack.begin(); it != Mypack.end(); it++) {
			if (it->second->getType() != PACK_EMPTY) {
				auto tmp = std::static_pointer_cast<Not_empty_pack>(it->second);
				if ((tmp->getFlag() == 1) && (tmp->getRelease() != tmp->getreleaselast())){
					tmp->setReleaselast(tmp->getRelease());
					os << "update:" << tmp->getName() << std::endl;
				}
			}

		}
	
	};
	bool Manager::update_pack(string name) {
		auto t = Mypack.find(name);
		if (t == Mypack.end())
			return 1;
		auto tmp = std::static_pointer_cast<Not_empty_pack>(t->second);
		tmp->update_pack();
	}

	bool Manager::delete_pack(string name) {
		auto t = Mypack.find(name);
		if (t == Mypack.end())
			return 1;
		t->second->delete_f_rep(Mypack);
		return 0;

	}

	bool  Manager::add(int type, int flag, std::string name, std::string author, int max, int now, int n, Vector<string> link) {

		if (type == PACK_EMPTY) {
			shared_ptr<Empty_pack> New = std::make_shared<Empty_pack>(flag, name, author, n);
			Mypack[name] = New;

		}
		else if (type == PACK_SOFT) {
			shared_ptr<Pack_soft> New = std::make_shared<Pack_soft>(flag, name, author, max, now, n);
			Mypack[name] = New;
			add_link(New, n, link);
		
		}
		else if (type == PACK_MI) {
			shared_ptr<Pack_MI> New = std::make_shared<Pack_MI>(flag, name, author, max, now, n);
			Mypack[name] = New;

			add_link(New, n, link);

		}
		else
			return 1;



		return 0;
	};
	bool Manager::add_link(shared_ptr<Not_empty_pack> New,int n,Vector<string> link) {
			for (int i = 0; i < n; i++) {
				auto t = Mypack.find(link[i]);
				if (t != Mypack.end()) {
					New->link.push_back(t->second);
				}
			}
			return 0;

	}
	;

}