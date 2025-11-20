# System Programming Examples

A collection of hands-on examples demonstrating core system programming concepts including inter-process communication, process management, and Unix/Linux system internals.

---

## 📂 Project Structure

### 1. **Bidirectional Communication** (`bidirection_comm/`)
Implementation of bidirectional IPC between parent-child processes using pipes.

**Files:**
- `02_ipc_pipe_bidirectional.cpp` - Interactive chat system with continuous communication

**Concepts Covered:**
- Two-pipe bidirectional communication
- Protocol design to avoid deadlocks
- Blocking I/O behavior
- Graceful shutdown handling
- Process synchronization via pipes

**Key Learning:**
- Parent→Child pipe and Child→Parent pipe
- Alternating write/read pattern prevents deadlock
- Proper closure of 4 unused pipe ends
- Using `wait()` to prevent zombie processes

---

### 2. **Shell Command Simulation** (`command_simulation/`)
Replicating shell pipeline behavior using processes and pipes.

**Files:**
- `csim.cpp` - Simulates `ls | wc -l` command

**Concepts Covered:**
- File descriptor redirection with `dup2()`
- Multi-process coordination
- Unidirectional pipe communication
- Process image replacement with `execlp()`
- Understanding stdin/stdout as file descriptors

**Key Learning:**
- File descriptor table manipulation
- `dup2(old_fd, new_fd)` redirects file descriptors
- Parallel process execution with pipe synchronization
- Producer-consumer pattern with flow control
- "Everything is a file" Unix philosophy

**How it Works:**
```
1. Parent creates pipe
2. Fork child1 (ls)
   - Redirect stdout → pipe write end
   - Execute ls (output goes to pipe)
3. Fork child2 (wc)
   - Redirect stdin → pipe read end  
   - Execute wc -l (reads from pipe)
4. Parent waits for both children
5. wc outputs line count
```

---

## 🎓 Learning Resources

### Complete Guides
- [Pipe Learning Guide](PIPE_LEARNING_GUIDE.md) - Comprehensive IPC tutorial with:
  - Progressive difficulty levels
  - Deadlock scenarios explained
  - Interview questions covered
  - Hands-on practice problems

---

## 🔗 Related Projects

**Main Concurrency Folder:** [../../concurrency/](../../concurrency/)
- Basic pipe examples
- Process vs Thread fundamentals
- Thread/Process creation syntax
- Memory layout and internals

---

## 🎯 Interview Preparation

### Topics Covered:
✅ **Pipe-based IPC**
- Unidirectional and bidirectional communication
- Deadlock scenarios and prevention
- Pipe buffer size and flow control

✅ **File Descriptors**
- stdin (0), stdout (1), stderr (2)
- File descriptor table per process
- Redirection with `dup2()`

✅ **Process Management**
- `fork()` - Process creation
- `execlp()` - Process image replacement
- `wait()` - Preventing zombies

✅ **Shell Internals**
- How pipelines work (`cmd1 | cmd2`)
- stdout/stdin redirection
- Multi-process coordination

---

## 🚀 Common Interview Questions Answered

1. **How does shell implement `cmd1 | cmd2`?**
   - See `command_simulation/csim.cpp`

2. **How to implement bidirectional communication between processes?**
   - See `bidirection_comm/02_ipc_pipe_bidirectional.cpp`

3. **What causes pipe deadlocks?**
   - Both processes reading first (circular wait)
   - Both processes writing large data (buffer full)
   - See PIPE_LEARNING_GUIDE.md for detailed scenarios

4. **Explain `dup2()` and file descriptor redirection**
   - Changes what a file descriptor points to
   - Used for stdout/stdin redirection
   - See `csim.cpp` implementation

5. **Can processes run in parallel with pipes?**
   - Yes, pipe provides synchronization
   - Producer-consumer pattern with flow control
   - Pipe buffer acts as queue between processes

---

## 📊 Compilation & Running

All projects use the same Makefile pattern:

```bash
# In any project directory
make FILE=<filename>.cpp run

# Example:
cd bidirection_comm
make FILE=02_ipc_pipe_bidirectional.cpp run

cd ../command_simulation
make FILE=csim.cpp run
```

---

## 🎓 Learning Progress

| Topic | Example | Status | Interview Ready |
|-------|---------|--------|-----------------|
| Basic Pipes | [concurrency/02_ipc_pipe_basics.cpp](../../concurrency/02_ipc_pipe_basics.cpp) | ✅ | ✅ |
| Bidirectional IPC | bidirection_comm/ | ✅ | ✅ |
| Shell Pipelines | command_simulation/ | ✅ | ✅ |
| File Descriptors | csim.cpp | ✅ | ✅ |
| Process Management | All examples | ✅ | ✅ |
| Deadlock Scenarios | PIPE_LEARNING_GUIDE.md | ✅ | ✅ |

---

## 🌟 Key Takeaways

### Pipes
- ✅ Unidirectional: One pipe, one direction
- ✅ Bidirectional: Two pipes required
- ✅ `read()` blocks until data available
- ✅ Close unused ends to prevent deadlocks
- ✅ Buffer size: ~64KB (check with `ulimit -p`)

### File Descriptors
- ✅ FD table per process (kernel memory)
- ✅ 0=stdin, 1=stdout, 2=stderr
- ✅ `dup2()` changes what FD points to
- ✅ "Everything is a file" in Unix

### Process Communication
- ✅ Pipes for parent-child/siblings
- ✅ Named pipes (FIFO) for unrelated processes
- ✅ Shared memory for high performance
- ✅ Always use `wait()` to prevent zombies

### Parallel Execution
- ✅ Multiple processes can run simultaneously
- ✅ Pipe provides synchronization
- ✅ Flow control via blocking I/O
- ✅ Producer-consumer pattern naturally emerges

---

## 📚 Next Steps

**Completed:**
- Basic pipe communication
- Bidirectional communication
- Shell pipeline simulation

**Coming Next:**
- Named pipes (FIFO)
- Shared memory IPC
- Message queues
- Synchronization primitives (mutex, semaphores)
- Multi-threaded servers

---

**Happy Learning! 🚀**
