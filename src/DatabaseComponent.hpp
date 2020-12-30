
#ifndef CRUD_DATABASECOMPONENT_HPP
#define CRUD_DATABASECOMPONENT_HPP

#include "db/UrlDb.hpp"

class DatabaseComponent {
public:

  /**
   * Create database client
   */
//  OATPP_CREATE_COMPONENT(std::shared_ptr<UserDb>, userDb)([] {
  OATPP_CREATE_COMPONENT(std::shared_ptr<UrlDb>, urlDb)([] {

    /* Create database-specific ConnectionProvider */
    auto connectionProvider = std::make_shared<oatpp::sqlite::ConnectionProvider>(DATABASE_FILE);

    /* Create database-specific ConnectionPool */
    auto connectionPool = oatpp::sqlite::ConnectionPool::createShared(connectionProvider,
                                                                      10 /* max-connections */,
                                                                      std::chrono::seconds(5) /* connection TTL */);

    /* Create database-specific Executor */
    auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionPool);

    /* Create MyClient database client */
    return std::make_shared<UrlDb>(executor);

  }());


};

#endif //CRUD_DATABASECOMPONENT_HPP
