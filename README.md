# IO Word Manager in C

## Description
This is a menu-driven C program that allows the user to manage up to 1000 words:
- Add words
- View current word list
- Remove words (with confirmation)
- Track how many words were deleted during session
- Log deleted words to `deleted_log.txt` with timestamps
- Save/load words using a binary file (`words.bin`)

## Features
- No global variables
- Binary file I/O
- Text-based logging for deleted words
- Safe deletion with user confirmation
- Modular design using functions

## How to Compile
```bash
gcc -o word_manager word_manager.c
```

## How to Run
```bash
./word_manager
```

## Output Files
- `words.bin`: Stores current word list between sessions
- `deleted_log.txt`: Log of deleted words with timestamps
