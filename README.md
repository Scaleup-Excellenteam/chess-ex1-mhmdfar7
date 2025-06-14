<table>
<tr style="border: none">
<td style="border: none">

# THE Chess Template Repository

</td>
<td align="right" style="border: none">
<img src="./img/scaleup.png" alt="Scaleup" height="100">
</td>
</tr>
</table>

This is a template repository for the Tel Hai Excellenteam (THE) CPP course.

All exercises and submissions should follow the format of this repository. For your convenience, you can start each assignment by cloning this template.

## Environment Setup
During the course we will utilize Linux based operating system (OS), to run and execute programs.

### Windows Installation
1. Install [WSL 2](https://learn.microsoft.com/en-us/windows/wsl/install), with Ubuntu distribution.

### Mac Installation
1. Follow the instruction presented in the following [video](https://www.youtube.com/watch?v=LjL_N0OZxvY), install Ubuntu (no GUI) version.
2. To install GUI, use following [guide](https://askubuntu.com/questions/53822/how-do-you-run-ubuntu-server-with-a-gui)
3. In case you forgot the default credentials, read following [article](https://www.debugpoint.com/virtualbox-id-password/)

### Linux Installation
Ensure you have `g++`, `CMake`, and `make` installed:

```sh
sudo apt update
sudo apt install -y g++ cmake make
```

## Grading and Conventions
Your assignment will be graded according to the following criteria. Please make sure your assignment follows the standards and conventions outlined below:

For best practices please use examples presented in [PRACTICES.md](PRACTICES.md), if still there is an uncertainty or missing use cases, you are highly encouraged to contact the staff for further clarifications.

### Branching
Use the [CONTRIBUTING.md](CONTRIBUTING.md) file as your guideline for proper use of Git. For more information, you are encouraged to search online for "[GitHub Workflow Methodology](https://www.youtube.com/watch?v=U_IFGpJDbeU&ab_channel=DevOpsToolkit)."

### Repository Structure
Please follow the guidelines in this section strictly.

- The repository should include a `CMakeLists.txt` file at the root directory.
- The repository **MUST NOT** include any compiled binaries (e.g., build/, .o files, a.out, or any other generated executables). (Put those file names in `.gitignore` file)

<p align="center">
  <img src="./img/cpp-logo.png" alt="C++ Logo" width="100" height="100">
  <img src="./img/linux-logo.jpg" alt="Linux Logo" width="100" height="100">
</p>

#### GitHub Configuration
* The repository should include a `README.md` file at the root directory.
* The repository should include a `CONTRIBUTING.md` file at the root directory.
* You must have a `.gitignore` file, and there shouldn’t be any unnecessary files in the repository.
* 🚨 **CRITICAL:** Repositories without a workflow file at `.github/workflows/c-cpp.yml` will not be graded. :(
* You must have an `img` directory at the root directory.

#### Project's Files
- The repository should include a `main.cpp` file in src directory.
- The repository should include a `src` directory at the root.
  - All source files should be placed in the `src` directory.
- The repository should include a `include` directory at the root.
  - All `.h` files should be placed in the `include` directory.
- The repository should include a `test` directory at the root.
  - All tests should be placed in the `test` directory.

#### Project Tree

```bash
.
├── CONTRIBUTING.md
├── .git
│   ├── ...
├── .github
│   └── workflows
│       └── c-cpp.yml
├── .gitignore
├── img
│   ├── excellenteam.png
│   ├── scaleup.png
│   └── cpp_logo.png
├── README.md
├── CMakeLists.txt
├── src
│   ├── main.cpp
│   ├── ...
├── include
│   ├── ...
├── tests
│   ├── ...
```

## Compilation Instructions

```bash
mkdir -p build
cd build
cmake ..
make
./Chess
```

Any project that does not compile properly using these steps will not be graded.

## How to Submit an Exercise
You are required to submit each exercise using "GitHub Classroom". To do this, you must upload a link to your "GitHub Classroom" repository via Moodle.

### Branching and Pull Request Guidelines

- 🚨 Your `main` branch **must remain clean and stable** at all times. Never push directly to `main`.  
- Create a **new branch** from `main` for each exercise (e.g., `exercise1`, `feature/queen-movement`, etc.).  
- Work on those branches and push your changes there.  
- Once you're done, open a **Pull Request (PR)** from your branch where all the changes were made into `main`.  
- In the PR, review your changes carefully using GitHub’s diff viewer.  
- Make sure all checks pass (e.g., linter, build).  
- After merging the PR into `main`, you can submit the repository link via Moodle.

### Pre-submission Checkup
1. Make sure you've answered all the questions.  
2. Review and refactor your code for better readability.  
3. Ensure that all intended files are uploaded to Git and follow the structure convention.  
4. Ensure that your code is running.  
5. Review changes in your PR carefully.  
6. Make sure the linter passed.  
7. Follow the branching guidelines.  
8. Upload the repository link to Moodle.  
9. Good luck :)

---

## 📦 Part 4: Project Summary & Reflection

### ✔️ Features Implemented:
- [x] Game mode: Player vs Player / Player vs Computer
- [x] AI opponent (with multithreaded move evaluation)
- [x] User-defined depth (`--depth`) and threads (`--threads`)
- [x] Checkmate detection
- [x] Castling: kingside & queenside, both sides
- [x] Stalemate (draw) detection

### 🧠 AI:
- Uses parallel move evaluation with a thread pool and priority queue
- Selects highest scoring legal move based on depth-limited evaluation

### 🧪 Testing:
- Tested castling, stalemate, and checkmate scenarios manually
- Verified rook movement during castling and check legality
- Confirmed AI does not make illegal moves
- Simulated edge cases like castling through check, invalid input, and blocked paths

### ⚙️ Challenges:
- Implementing full castling rule logic with state tracking (`hasMoved`)
- Adding deep copy support for board with polymorphic `clone()` methods
- Ensuring thread safety in AI decision-making

### 💡 Future Improvements:
- Undo and save/load features
- GUI instead of terminal
- Full FEN support and move notation
- 50-move rule and threefold repetition detection
