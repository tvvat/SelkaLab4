#pragma once

#include <string>
#include "Vector.h"
#include <map>
#include <memory>
namespace Prog4 {


	/*struct option 
	{
		int flag;
		std::string name;
		std::string author_name;
		int inst_version;

	}opt;*/


	enum DEFINE {
		PACK_MI = 0,
		PACK_SOFT,
		PACK_EMPTY

	};
	class Pack;

	class Pack_soft;
	class Pack {
	private:
		int flag;
		std::string name;
		std::string author_name;
		int num_cviz;
	public:
		Pack(int , std::string, std::string,  int );/*
		int add_to_rep(std::map <std::string, std::shared_ptr<Pack>> &);*/


		/**
		* @brief show info of file
		*
		**/
		void output_into();

		/**
		* @brief delet thid pac from rep
		* @param "rep"=repository where lie this pack
		*
		**/
		int delete_f_rep(std::map <std::string, std::shared_ptr<Pack>>& );
		
		/**
		* @brief prog return Name
		*
		**/
		std::string getName() { return name; };
		/**
		* @brief prog return Autor
		*
		**/
		std::string getAutor() { return author_name;};
		/**
		* @brief prog return 1 if file install else 0;
		*
		**/
		int getFlag() { return flag; };
		/**
		* @brief prog return num of link
		*
		**/
		int getNum() { return num_cviz; };

		/**
		* @brief prog install Name
		* @param "name"= new name
		*
		**/
		void setName(std::string );

		/**
		* @brief prog install Name  autor
		* @param "name"= new name
		*
		**/
		void setAutor(std::string);

		/**
		* @brief prog install flag
		* @param "flag"= new flag
		*
		**/
		void setFlag(int );
		/**
		* @brief prog install Num
		* @param "num"= new number of link
		*
		**/
		void setNum(int);
		/**
		* @brief prog  control that frep will ba acirclegraph
		* @param "pack"= our new pack
		* @param "rep"include link
		*
		**/
		int agraph(std::shared_ptr<Pack_soft>, Vector<std::string>);
		/**
		* @brief prog return type pack
		*
		**/
		virtual DEFINE getType() = 0;

		~Pack() = default;
	};
	class Empty_pack : public Pack {


	public:
		Empty_pack(int fl = 0, std::string n = "Empty", std::string a = "autor_mane",int t = 0) : Pack(fl, n, a,  t) {};
		DEFINE getType() { return PACK_EMPTY; };
		
	};
	class Not_empty_pack : public Pack{
	public:
		int last_version;
		int inst_version;
		Vector <std::shared_ptr<Empty_pack>> link_empty_pack;
		Vector <std::shared_ptr<Pack> > link;
	public:
		Not_empty_pack(int fl = 0, std::string n = "MI", std::string a = "autor_mane", int release = 1,int last_release = 1, int t = 0) : Pack(fl,n,a,t) {
			inst_version = release;
			if (fl == 1)
				if (last_release > inst_version)
					last_version = inst_version;
				else
					last_version = last_release;
			else
				
				last_version = 0;
		};


		/**
		* @brief relese increase release for 1
		*
		**/
		void update_pack();
		/**
		* @brief prog return now release
		*
		**/
		int getreleaselast() { return last_version; }

		/**
		* @brief prog return max release
		*
		**/
		int getRelease() { return inst_version; };
		/**
		* @brief prog set now release
		* @param "r"=this release install
		*
		**/
		void setReleaselast(int);
		/**
		* @brief prog set max release
		* @param "r"=this release install
		**/
		void setRelease(int);

		/**
		* @brief prog unification this pack with rep save links
		* @param "rep"=repository with pack which unification with this
		*
		**/
		int unification(std::map <std::string, std::shared_ptr<Pack>>&  );
	};

	class Pack_MI : public Not_empty_pack {

	public:
		Pack_MI(int fl = 0, std::string n = "MI", std::string a = "autor_mane", int release = 1, int last_release = 1, int t = 0) : Not_empty_pack(fl, n, a, release, last_release,t) {};
		DEFINE getType() { return PACK_MI; };
	};

	class Pack_soft : public Not_empty_pack{

	public:
		Pack_soft(int fl = 0, std::string n = "soft", std::string a = "autor_mane", int release = 1, int last_release = 1, int t = 0) : Not_empty_pack(fl, n, a, release,last_release, t) {};

		/**
		* @brief prog separetin this pack and return vector with  new pack 
		* @param "name"=name for new pack
		* @param "release"=version for new pack
		**/
		Vector<std::shared_ptr<Pack>> separation(Vector<std::string >,Vector<int> );
		DEFINE getType() { return PACK_SOFT; };
		
	};
}