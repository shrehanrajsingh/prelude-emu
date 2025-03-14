# Instructions And Layout
## 📝 Registers
| Register | Purpose |
|----------|---------|
| A | General purpose register |
| B | General purpose register |
| C | General purpose register |
| D | General purpose register |
| E | General purpose register |
| F | General purpose register |

## 🔧 Instructions
| Instruction | Description |
|-------------|-------------|
| `mov` | Move data between registers |
| `add` | Add values |
| `push` | Push to stack |
| `pop` | Pop from stack |
| `halt` | Stop execution |

## 📚 Stack
```
+----------+
|    ...   | <- Stack grows downward
+----------+
```

## 🖥️ How a SYSCALL works
A syscall requires the use of registers:

- It requires a minimum of one register (`A`)
- The first register, A, takes the library for which the syscall is called
    - A = 1 → Standard file operations
    - etc.
- The second, third and so on, registers take in arguments
- Almost always, the return value will be stored in register A