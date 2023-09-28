CREATE TABLE stock_transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER NOT NULL,
    type TEXT NOT NULL,
    stock_name TEXT NOT NULL,
    total_shares INTEGER NOT NULL,
    share_value NUMERIC NOT NULL,
    transaction_value NUMERIC NOT NULL,
    transaction_date TEXT NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users (id)
);