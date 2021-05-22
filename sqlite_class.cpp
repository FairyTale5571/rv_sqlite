#include "sqlite_class.hpp"

RvSqlite::RvSqlite()
:
	rc(-1),
	database(0),
	errorMsg("error"),
	dbName("")
{
	
}

RvSqlite::RvSqlite(std::string dbFile)
:
	rc(-1),
	database(0),
	errorMsg("error"),
	dbName(dbFile)
{
}

int RvSqlite::open()
{
	FILE* fPtr;
	boost::filesystem::path here();
	
}

int RvSqlite::close()
{

}

void RvSqlite::set_name(std::string s)
{
	dbName = s;
}


int RvSqlite::error_and_close()
{


}

const char* RvSqlite::get_err_msg()
{

}

int RvSqlite::read(std::string sql)
{

}

int RvSqlite::exec(std::string sql)
{

}

int RvSqlite::step(sqlite3_stmt* statement)
{

}

int RvSqlite::status()
{

}

sqlite3_stmt* RvSqlite::prepare(std::string sql)
{


}
