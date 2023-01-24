#pragma once
#include <map>
#include <string>
#include <iostream>
#include "framework.h"


using namespace std;
namespace Prog4 {


	class Manager {
	private:
		map <std::string, shared_ptr<Pack>> Mypack;
	public:


		/**
		* @brief prog separetin this pack and return vector with  new pack
		* @param "define"=type of pack 0 MI, 1 soft,2 empty
		* @param "name"=version for new pack
		* @param "flag"=1 instal else 0
		* @param "name autor"=autor name
		* @param "maxrelese " = release max
		* @param "nowrelease" = release now
		* @param "name" = name include pack	
		* 
		**/
		bool auto_inst_file(int , string , int , string , int, int,Vector <string> );

		/**
		* @brief show info about pack
		**/
		bool show(std::ostream& os);

		/**
		* @brief check that Mi pack dont include pack 
		* @param "name" = name pack
		**/
		bool check(std::string );
		/**
		* @brief if flag MI = 1 prog install pack
		* @param "name" = name pack 
		* @param "flag" = flag mainl pack
		**/
		int instlibforMI(std::string, int);

		/**
		* @brief set flag 1 for all dont used soft
		**/
		bool cleaning();

		
		/**
		* @brief install pack with iclude lib
		**/
		bool auto_inst(std::string );
		/**
		* @brief recursion  install all pack whith link
		**/
		int setflag1auto(std::shared_ptr<Not_empty_pack>);
		/**
		* @brief install pack with iclude lib
		**/
		bool ask_inst(std::string);


		/**
		* @brief install pack with iclude lib after ask
		**/
		int setflag1ask(std::shared_ptr<Not_empty_pack>);
		/**
		* @brief delete pack with all link
		* @param "name" = name delet main pack
		* @param "flag" = if 1 then delet all link without ASK ELSE 0 ask about evry one file
		**/
		bool delete_pack(std::string, int flag);

		/**
		* @brief that this file dont used
		* @param "name" = name check pack
		**/
		int checkmum(std::string);
		/**
		* @brief rec then delet all link without ASK
		* @param "pack" = which delet
		**/
		int delet_rec(std::shared_ptr<Not_empty_pack>); 
		/**
		* @brief rec then delet all link ASK
		* @param "pack" = which delet
		**/
		int delet_rec_ask(std::shared_ptr<Not_empty_pack>);
		/*void cleaning();*/
		/**
		* @brief set max release for install pack
		**/
		void glob_update(std::ostream& os);
		/**
		* @brief unification 
		* @param "pack" = which where unification
		* @param "packs" = pack which will unification
		**/
		bool unification(string , Vector<string> );


		/**
		* @brief separation soft, add new packs
		* @param "pack" = which separation
		* @param "name" = name new paks
		* @param "release" = release new paks
		**/
		bool separation(string, Vector<string> ,Vector<int>);
		/**
		* @brief prog separetin this pack and return vector with  new pack
		* @param "define"=type of pack 0 MI, 1 soft,2 empty
		* @param "name"=version for new pack
		* @param "flag"=1 instal else 0
		* @param "name autor"=autor name
		* @param "maxrelese " = release max
		* @param "nowrelease" = release now
		* @param "link" = name include pack
		*
		**/
		bool add(int, int, std::string, std::string, int, int, int,Vector<string>);
		/**
		* @brief rec add link
		* @param "pack" = where add 
		* @param "n" = count of add 
		* @param "name" = name of add 
		**/
		bool add_link(shared_ptr<Not_empty_pack> ,int, Vector<string> );
		/**
		* @brief relese increase release for 1
		* @param "name" = pack wich release increase
		**/
		bool update_pack(string);

		/**
		* @brief delet this pack from rep
		* @param "name"=delet pack
		*
		**/
		bool delete_pack(string);
	};

}