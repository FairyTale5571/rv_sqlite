#pragma once

#include "pch.h"

#include "3rd\easylogging++.h"
INITIALIZE_EASYLOGGINGPP

using namespace std;

class RvSqlite
{

	private:
		int rc;
		sqlite3* database;
		std::string dbPassword;
		std::string dbName;
		std::string errorMsg;

	public:
	
		RvSqlite();
		RvSqlite(std::string dbFile);

		~RvSqlite()
		{
			close();
		};

		int open();
		int close();
		int error_and_close();
	
		int get_rc() const { return rc; };
		std::string get_name() const { return dbName; };

		void set_name(std::string s);
		
		sqlite3_stmt* prepare(std::string s);
		int step(sqlite3_stmt* statement);
		int status();
		int read(std::string sql);

		int exec( std::string sql );
		const char* get_err_msg();

};
