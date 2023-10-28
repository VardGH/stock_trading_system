# Trading Platform

The **Trading Platform** is a C++ project that simulates a trading environment. It includes components for managing balances, stocks, traders, and executing orders in a threaded environment.

## Components

### 1. Balance Factory

- Provides a singleton instance for managing balance creation and manipulation.
- Reads balance data from a specified file path.
- Processes stock data and updates balance instances.

### 2. Balance Service

- Singleton service for managing balance profiles.
- Registers balance profiles with unique profile IDs.

### 3. Balance Class

- Represents a balance profile with an initial balance and stocks.
- Tracks profile ID, current balance, and stocks.

### 4. Hot Wallet

- Represents a hot wallet for storing registered stocks.
- Singleton instance for managing registered stocks.

### 5. Order System

- `order` class represents a generic order with common attributes and actions.
- `market_order` class represents a market order that executes immediately.
- `limit_order` class represents a limit order that executes at a specified price or better.
- `order_factory` provides a static method to create instances of orders based on the order type.

### 6. Platform

- Manages the overall trading platform.
- Includes functions for setup, start, and stopping the platform.
- Utilizes a singleton pattern.

### 7. Stock Factory

- Provides a singleton instance for managing stock creation and manipulation.
- Reads stock data from a specified file path.

### 8. Stock Class

- Represents a stock with a symbol, initial price, and quantity.
- Tracks the stock symbol, current price, and quantity.
- Supports randomizing the stock's current price.

### 9. Thread Pool

- Represents a pool of threads for executing asynchronous tasks.
- Supports submitting tasks for execution.

### 10. Trader Service

- Singleton service for managing trader registration.
- Registers traders with unique trader IDs.

### 11. Trader Class

- Represents a trader with a trader ID and name.
- Tracks the trader's ID and name.

## Usage

1. **Platform Setup and Start:**
   - Use the `platform` class to set up and start the trading platform.

```cpp
platform& trading_platform = platform::get();
trading_platform.start();
```

2. **Balance Management:**
   - Use the `balance_factory` to create and manage balance profiles.
   - Use the `balance_service` to register and manage balance profiles.

```cpp
balance_factory& bal_factory = balance_factory::get();
balance_service& bal_service = balance_service::get();

// Create a new balance profile
balance new_balance(1, 10000.0);
bal_factory.process_stock_data(new_balance, "AAPL:50,GOOGL:20");
bal_service.register_balance(1, std::move(new_balance));
```

3. **Stock Management:**
   - Use the `stock_factory` to create and manage stock instances.

```cpp
stock_factory& stock_factory = stock_factory::get();

// Read stock data from a file
stock_factory.read_stock_db("stock_data.txt");
```

4. **Order Execution:**
   - Use the `order`, `market_order`, `limit_order`, and `order_factory` classes to create and execute orders.

```cpp
order* buy_order = order_factory::create_order("Limit", 1, 101, "AAPL", 150.0, 10);
buy_order->buy(); // Execute the buy order

order* sell_order = order_factory::create_order("Market", 2, 102, "GOOGL", 0.0, 5);
sell_order->sell(); // Execute the sell order
```

5. **Trader Management:**
   - Use the `trader_service` to register and manage traders.

```cpp
trader_service& tr_service = trader_service::get();

// Register a new trader
trader new_trader(101, "John Doe");
tr_service.register_trader(101, std::move(new_trader));
```