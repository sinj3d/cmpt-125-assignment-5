# Connect Four Plus! 🎮

A feature-rich console-based **Connect Four** game written in C++ with a twist! In addition to the standard rules, each player has access to a special **Anvil** piece that destroys all pieces in a column when dropped.

This project was built as the CMPT 125 Assignment 5 Final Project at Simon Fraser University.

## 🌟 Features

- **Player vs Player & Player vs Computer modes**
- **Minimax AI** opponent with multiple difficulty levels and alpha-beta pruning optimization.
- **Experimental Neural Network AI** trained using PyTorch on games simulated by the Minimax bot.
- **The Anvil**: A one-time use special utility piece that completely clears the entire column it's dropped into and rests securely at the bottom.
- Custom stylized console interface featuring "big" 3x3 characters, dynamic legends, and robust user input validation.

## 📂 Project Structure

- `a5.cpp`: The core game loop, Minimax algorithm implementation, and the User Interface rendering logic.
- `a5.h`: Headers/declarations for the game state properties (`Player`, `GameState`).
- `data_collector.cpp` & `data_collector.h`: Contains utilities allowing bots to battle each other to automatically track board states and generate CSV tracking data.
- `train_model.py`: An external PyTorch machine-learning script that trains a Feed-Forward Neural Network against our generated `data_collector` datasets to evaluate efficient moves.
- `neural_net.cpp` & `neural_net.h`: A completely custom, lightweight, pure C++ inference engine that evaluates moves by parsing mathematical PyTorch model weights directly, guaranteeing no external PyTorch compilation dependencies.
- `weights.txt`: The text-exported parameters calculated by PyTorch and interpreted smoothly into C++ floats by our Neural Net class.
- `a5_report.txt`: Technical project documentation for marking and grading expectations.
- `makefile`: Standard GNU Make utility to cleanly compile all required objects and headers.

## 🛠️ How to Compile & Run

To compile the primary C++ program using the provided assignment makefile (requires `g++` and standard C++17 library):

```bash
make a5
```

Afterward, run the executable:

```bash
./a5  # (or a5.exe on Windows)
```

## 👨‍💻 Team Contributions

This repository was collaboratively developed by:

- **Shenghua Jin**: Architecture, theoretical design, and implementation of the AI features (Minimax with alpha-beta pruning and the Neural Network inference logic), as well as supportive class functions.
- **Luke Choi**: Implemented the primary mechanics via the main function execution, `GameState`/`Player` class logic, core game loops, and the stylized console UI rendering.
  
*(Note: Because of assignment restrictions requiring pure standard C++ with standard compilation rules, the Machine Learning Python pipelines are included for reference but operate entirely distinct from the required runtime compilation.)*
