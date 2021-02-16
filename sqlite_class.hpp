#pragma once

#include "pch.h"

#include "3rd\easylogging++.h"
INITIALIZE_EASYLOGGINGPP

using namespace std;

class SQLITE
{
	public:

		SQLITE()
		:
			rc(-1),
			database(0),
			errorMsg("error"),
			dbName("")
		{}

		SQLITE(std::string dbFile)
		:
			rc(-1),
			database(0),
			errorMsg("error"),
			dbName(dbFile)
		{}

		~SQLITE() 
		{
			close();
		};

		int open();
		int close();
		int error_and_close();
	
		int get_rc() { return rc; };
		void set_name(std::string s);
		std::string get_name() { return dbName; };
		
		sqlite3_stmt* prepare(std::string s);
		int step(sqlite3_stmt* statement);
		int status();

		int exec( std::string sql );
		const char* get_err_msg();


	private:
		int rc;
		sqlite3* database;
		std::string dbName;
		std::string errorMsg;
};

int SQLITE::open()
{
	FILE* fPtr;
	fPtr = fopen(dbName.c_str(), "r");
	if (!fPtr)
	{
		//-- Create database file if not exist
		rc = sqlite3_open_v2(dbName.c_str(), &database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
		if (rc)
			error_and_close();

	} else {
		//-- Open exist database
		rc = sqlite3_open_v2(dbName.c_str(), &database, SQLITE_OPEN_READWRITE, nullptr);
		if (rc)
			error_and_close();
		fclose(fPtr);
	}
	LOG(INFO) << "Opened: " << database << endl;

	LOG(INFO) << "Opened: " << dbName << " ? " << status() << endl;

	return rc;
}

int SQLITE::close()
{
	rc = sqlite3_close(database);

	return rc;
}

void SQLITE::set_name(std::string s)
{
	dbName = s;
}

int SQLITE::error_and_close()
{
	LOG(ERROR) << 
		"Error to open database: " << dbName << " " << 
		sqlite3_errmsg(database) << endl;

	sqlite3_close(database);
	
	return rc;
}

const char* SQLITE::get_err_msg()
{
	return sqlite3_errstr(rc);
}

int SQLITE::exec(std::string sql)
{
	
	sqlite3_stmt* statement = prepare(sql);
	rc = step(statement);
	
	return rc;
}

int SQLITE::step(sqlite3_stmt* statement)
{
	LOG(INFO) << "Status before step: " << status() << endl;

	rc = sqlite3_step(statement);
	if (rc == SQLITE_ERROR)
	{
		LOG(ERROR) <<
			"Error to execute statement: " << sqlite3_errmsg(database) << endl <<
			sqlite3_errstr(rc) << endl <<
			"Statement: " << statement << endl;

		sqlite3_free(database);
		sqlite3_close(database);
		return rc;
	}
	sqlite3_finalize(statement);
	return rc;
}

int SQLITE::status()
{
	int cacheSize = 0;
	int dummy;
	int rc = sqlite3_db_status(database, SQLITE_DBSTATUS_CACHE_USED, &cacheSize, &dummy, 0);
	if (rc != SQLITE_OK)
	{
		std::cerr << "Status: Cache used: " << rc << endl;
	}
	
	return rc;
}

sqlite3_stmt* SQLITE::prepare(std::string sql)
{

	std::cout << "Status before prepare: " << status() << endl;

	sqlite3_stmt* statement;
	rc = sqlite3_prepare_v2(database, sql.c_str(), -1, &statement, NULL);
	if (rc != SQLITE_OK)
	{
		LOG(ERROR) <<
			"Error to prepare statement: " << sqlite3_errmsg(database) << endl <<
			sqlite3_errstr(rc) << endl <<
			"Statement: " << sql.c_str() << endl;

		sqlite3_free(database);
		sqlite3_close(database);
		return nullptr;
	}
	return statement;
}
