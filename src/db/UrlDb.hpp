
#ifndef CRUD_URLDB_HPP
#define CRUD_URLDB_HPP

#include "dto/UrlDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * UserDb client definitions.
 */
class UrlDb : public oatpp::orm::DbClient {
public:

  UrlDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
      : oatpp::orm::DbClient(executor)
  {

    oatpp::orm::SchemaMigration migration(executor);
    migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
    // TODO - Add more migrations here.
    migration.migrate(); // <-- run migrations. This guy will throw on error.

    auto version = executor->getSchemaVersion();
    OATPP_LOGD("UrlDb", "Migration - OK. Version=%d.", version);

  }

  QUERY(createUrl,
        "INSERT INTO AppUrl"
        "(url, shorten) VALUES "
        "(:url.url, :url.shorten);",
        PARAM(oatpp::Object<UrlDto>, url))

  QUERY(getByShorten,
        "SELECT * FROM AppUrl WHERE shorten=:shorten;",
        PARAM(oatpp::String, shorten))

  QUERY(updateAmount,
        "UPDATE AppUrl"
        "SET"
        " use_amount=:url.use_amount"
        "WHERE"
        " id=:url.id;",
        PARAM(oatpp::Object<UrlDto>, url))


};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //CRUD_USERDB_HPP
