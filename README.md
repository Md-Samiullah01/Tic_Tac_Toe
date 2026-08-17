# Tic_Tac_Toe

# Combined Tic Tac Toe Implementations (C & JavaScript/HTML)

This document combines both the CLI C version and the Web-based HTML/CSS/JS implementation of the classic **Tic Tac Toe** game into a single reference guide.

---

## 1. C Implementation (CLI Version)

### Overview
A terminal-based 2-player Tic Tac Toe implementation written in C. It uses a 1D array (`char a[10]`) mapped to indices 1 through 9 for turn management and win detection.

### Source Code

```c
#include <stdio.h>
#include <stdlib.h>

char board[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_title(void) {
    printf("
		 Tic Tac Toe
");
    printf("		-------------
");
}

void print_symbols(void) {
    printf("Player 1: 'X'  |  Player 2: 'O'

");
}

void display_board(void) {
    printf("		|---|---|---|
");
    printf("		| %c | %c | %c |
", board[1], board[2], board[3]);
    printf("		|---|---|---|
");
    printf("		| %c | %c | %c |
", board[4], board[5], board[6]);
    printf("		|---|---|---|
");
    printf("		| %c | %c | %c |
", board[7], board[8], board[9]);
    printf("		|---|---|---|

");
}

int check_winner(void) {
    // Horizontal wins
    if (board[1] == board[2] && board[2] == board[3]) return 1;
    if (board[4] == board[5] && board[5] == board[6]) return 1;
    if (board[7] == board[8] && board[8] == board[9]) return 1;

    // Vertical wins
    if (board[1] == board[4] && board[4] == board[7]) return 1;
    if (board[2] == board[5] && board[5] == board[8]) return 1;
    if (board[3] == board[6] && board[3] == board[9]) return 1;

    // Diagonal wins
    if (board[1] == board[5] && board[5] == board[9]) return 1;
    if (board[3] == board[5] && board[5] == board[7]) return 1;

    // Check for active cells remaining
    for (int i = 1; i <= 9; i++) {
        if (board[i] == (char)(i + '0')) {
            return -1; // Game active
        }
    }

    return 0; // Draw
}

int main(void) {
    int player = 1;
    int choice;
    int status = -1;
    char mark;

    do {
        clear_screen();
        print_title();
        print_symbols();
        display_board();

        player = (player % 2 != 0) ? 1 : 2;
        mark = (player == 1) ? 'X' : 'O';

        printf("Player %d (%c), enter a position (1-9): ", player, mark);
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '
');
            continue;
        }

        if (choice >= 1 && choice <= 9 && board[choice] == (char)(choice + '0')) {
            board[choice] = mark;
            status = check_winner();
            if (status == -1) {
                player++;
            }
        } else {
            printf("
Invalid move! Press Enter to try again...");
            while (getchar() != '
');
            getchar();
        }
    } while (status == -1);

    clear_screen();
    print_title();
    print_symbols();
    display_board();

    if (status == 1) {
        printf(" ==> Congratulations! Player %d (%c) Wins!

", player, mark);
    } else {
        printf(" ==> Game Over! It's a Draw.

");
    }

    return 0;
}
```

---

## 2. Web/JavaScript Implementation (GUI Version)

### Overview
A modern web-based Tic Tac Toe frontend built using HTML5, CSS3, and JavaScript. Features dynamic CSS color accents, score persistence for the session, turn toggling, and winning line highlights.

### Source Code

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <meta name="author" content="Sami" />
  <title>Tic Tac Toe</title>
  <style>
    :root {
      --bg: #1a1a2e;
      --card: #16213e;
      --tile: #0f3460;
      --accent-o: #e94560;
      --accent-x: #4cc9f0;
      --text: #ffffff;
      --radius: 12px;
    }
    
    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    }
    
    body {
      background: var(--bg);
      color: var(--text);
      display: flex;
      justify-content: center;
      align-items: center;
      min-height: 100vh;
      overflow: hidden;
    }
    
    .container {
      width: 100%;
      max-width: 400px;
      padding: 20px;
      text-align: center;
    }
    
    h1 {
      margin-bottom: 10px;
      font-weight: 300;
      letter-spacing: 2px;
    }
    
    .scoreboard {
      display: flex;
      justify-content: space-around;
      margin-bottom: 20px;
      background: var(--card);
      padding: 10px;
      border-radius: var(--radius);
    }
    
    .status-msg {
      height: 30px;
      margin-bottom: 15px;
      font-size: 1.2rem;
      font-weight: bold;
      color: var(--accent-x);
    }
    
    .game-grid {
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 10px;
      background: var(--card);
      padding: 10px;
      border-radius: var(--radius);
      box-shadow: 0 10px 30px rgba(0, 0, 0, 0.5);
    }
    
    .box {
      aspect-ratio: 1/1;
      background: var(--tile);
      border: none;
      border-radius: 8px;
      font-size: 2.5rem;
      font-weight: bold;
      cursor: pointer;
      transition: transform 0.1s, background 0.3s;
      display: flex;
      align-items: center;
      justify-content: center;
    }
    
    .box:hover:not(:disabled) {
      background: #1b497d;
      transform: scale(1.02);
    }
    
    .box:disabled {
      cursor: default;
    }
    
    .box.winner {
      background: #ffffff22;
      animation: pulse 1s infinite;
    }
    
    @keyframes pulse {
      0% {
        transform: scale(1);
      }
      50% {
        transform: scale(1.05);
      }
      100% {
        transform: scale(1);
      }
    }
    
    .controls {
      margin-top: 25px;
      display: flex;
      gap: 10px;
    }
    
    .btn {
      flex: 1;
      padding: 12px;
      border: none;
      border-radius: var(--radius);
      background: var(--accent-o);
      color: white;
      font-weight: bold;
      cursor: pointer;
      transition: opacity 0.2s;
    }
    
    .btn-reset {
      background: #444;
    }
    
    .btn:hover {
      opacity: 0.8;
    }
    
    .hide {
      display: none;
    }
  </style>
</head>

<body>
  <div class="container">
    <h1>TIC TAC TOE</h1>
    
    <div class="scoreboard">
      <div>Player O: <span id="scoreO">0</span></div>
      <div>Player X: <span id="scoreX">0</span></div>
    </div>
    
    <p class="status-msg" id="status">Player O's Turn</p>
    
    <div class="game-grid" id="board">
      <button class="box" data-index="0"></button>
      <button class="box" data-index="1"></button>
      <button class="box" data-index="2"></button>
      <button class="box" data-index="3"></button>
      <button class="box" data-index="4"></button>
      <button class="box" data-index="5"></button>
      <button class="box" data-index="6"></button>
      <button class="box" data-index="7"></button>
      <button class="box" data-index="8"></button>
    </div>
    
    <div class="controls">
      <button class="btn btn-reset" id="resetBtn">Reset Score</button>
      <button class="btn" id="newGameBtn">Next Round</button>
    </div>
  </div>
  
  <script>
    const board = document.getElementById("board");
    const boxes = document.querySelectorAll(".box");
    const statusTxt = document.getElementById("status");
    const newGameBtn = document.getElementById("newGameBtn");
    const resetBtn = document.getElementById("resetBtn");
    
    let scores = { O: 0, X: 0 };
    let turnO = true;
    let gameActive = true;
    
    const winPatterns = [
      [0, 1, 2],
      [3, 4, 5],
      [6, 7, 8],
      [0, 3, 6],
      [1, 4, 7],
      [2, 5, 8],
      [0, 4, 8],
      [2, 4, 6]
    ];
    
    board.addEventListener("click", (e) => {
      const box = e.target;
      if (!box.classList.contains("box") || box.innerText !== "" || !gameActive) return;
      
      const currentPlayer = turnO ? "O" : "X";
      box.innerText = currentPlayer;
      box.style.color = turnO ? "var(--accent-o)" : "var(--accent-x)";
      
      checkWinner();
      if (gameActive) {
        turnO = !turnO;
        statusTxt.innerText = `Player ${turnO ? "O" : "X"}'s Turn`;
        statusTxt.style.color = turnO ? "var(--accent-o)" : "var(--accent-x)";
      }
    });
    
    function checkWinner() {
      for (let pattern of winPatterns) {
        const [a, b, c] = pattern;
        if (boxes[a].innerText && boxes[a].innerText === boxes[b].innerText && boxes[a].innerText === boxes[c].innerText) {
          endGame(boxes[a].innerText, pattern);
          return;
        }
      }
      
      if ([...boxes].every(box => box.innerText !== "")) {
        endGame("Draw");
      }
    }
    
    function endGame(winner, pattern = null) {
      gameActive = false;
      if (winner === "Draw") {
        statusTxt.innerText = "It's a Draw!";
        statusTxt.style.color = "white";
      } else {
        statusTxt.innerText = `Winner: Player ${winner}!`;
        scores[winner]++;
        document.getElementById(`score${winner}`).innerText = scores[winner];
        pattern.forEach(index => boxes[index].classList.add("winner"));
      }
    }
    
    function startNewRound() {
      turnO = true;
      gameActive = true;
      statusTxt.innerText = "Player O's Turn";
      statusTxt.style.color = "var(--accent-o)";
      boxes.forEach(box => {
        box.innerText = "";
        box.classList.remove("winner");
      });
    }
    
    newGameBtn.addEventListener("click", startNewRound);
    resetBtn.addEventListener("click", () => {
      scores = { O: 0, X: 0 };
      document.getElementById("scoreO").innerText = "0";
      document.getElementById("scoreX").innerText = "0";
      startNewRound();
    });
  </script>
</body>
</html>
```

---

## 3. Comparison & Key Differences

| Feature | C Console Version | JavaScript/HTML GUI Version |
| :--- | :--- | :--- |
| **Interface** | Command Line Interface (Terminal) | Modern Web GUI (HTML/CSS Grid) |
| **Indexing** | 1-based indexing (`a[1]` to `a[9]`) | 0-based indexing (`0` to `8`) |
| **Input Handling** | `scanf()` terminal input | Event-driven (`click` event listeners) |
| **Scorekeeping** | Single session round | persistent score tracking per round |
| **Visual Effects** | ASCII text grid | CSS Animations (`pulse`) and colors |
