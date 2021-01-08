
CREATE TABLE AppUrl (
    id            INTEGER PRIMARY KEY,
    url           VARCHAR,
    shorten       VARCHAR UNIQUE,
    use_amount    INTEGER DEFAULT 0
);
