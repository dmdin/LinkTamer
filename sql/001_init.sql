
-- CREATE TABLE AppUser (
--     id          INTEGER PRIMARY KEY,
--     username    VARCHAR UNIQUE,
--     email       VARCHAR UNIQUE,
--     password    VARCHAR,
--     role        VARCHAR
-- );
--
-- INSERT INTO AppUser
-- (username, email, password, role) VALUES ('admin', 'admin@domain.com', 'admin', 'ROLE_ADMIN');

CREATE TABLE AppUrl (
    id            INTEGER PRIMARY KEY,
    url           VARCHAR UNIQUE,
    shorten       VARCHAR UNIQUE,
    use_amount    INTEGER DEFAULT 0,
);

-- INSERT INTO AppUrl (url, shorten) VALUES ('example.com', 'abc');