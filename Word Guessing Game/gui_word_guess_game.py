import tkinter as tk
import ttkbootstrap as tb
import random
import webbrowser

# Create the main window using ttkbootstrap theme
root = tb.Window(themename="darkly")
root.geometry('500x500')  # Set window size
root.resizable(0, 0)  # Disable window resizing
root.position_center()  # Position the window at the center of the screen
root.title("Word Guess Game")  # Set the window title

## variables
win = False  # Indicates whether the game has been won
hint_used = 0  # Flag to track if a hint has been used
guess_count = 0  # Count of attempts to guess the word
user_guess = ''  # User's current guess

# List of words to guess
words =[
    'ant', 'acid', 'apple', 
    'bear', 'ball', 'banana',
    'crab', 'cake', 'cherry',
    'deer', 'doll', 'date'
]
guess_word = random.choice(words)  # Randomly select a word from the list
print(guess_word)
# Widgets setup
user_guess_label = tb.Label(text="Guess the word : ")
user_guess_label.grid(row=0, column=0, padx=5, pady=5)

user_guess_entry = tb.Entry(root)
user_guess_entry.grid(row=0, column=1, padx=5, pady=10)
user_guess_entry.focus()  # Set focus on the user input entry field

try_label = tb.Label(text='')  # Label for displaying feedback on each guess
hint_label = tb.Label(text="")  # Label for hint-related messages
hint_btn_no = tb.Button(text="")  # Button for declining a hint
hint_btn_yes = tb.Button(text="")  # Button for accepting a hint

def open_url():
    # Open a URL in the default web browser
    url = "data:image/jpeg;base64,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"
    webbrowser.open(url)

def show_hint():
    global hint_used
    hint_used = 1
    user_guess_entry.delete(0, 'end')
    user_guess_entry.insert(0, guess_word[0])  # Provide a hint by filling in the first letter of the word
    hide_hint()

def hide_hint():
    hint_label.config(text="")
    user_guess_entry.focus()
    hint_btn_no.config(text='', width=0)
    hint_btn_no.grid_forget()
    hint_btn_yes.config(text='', width=0)
    hint_btn_yes.grid_forget()

def guess():
    global user_guess, guess_word, guess_count, win, hint_used
    while True:
        user_guess = user_guess_entry.get()
        if win == False:
            if user_guess == guess_word:
                guess_count += 1
                win = True
                try_label.config(text='')
                hint_label.config(text="")
                win_label = tb.Label(text=f"Congratulations\nYou WON!!!\nYou took {guess_count} try")
                win_label.grid(row=2, columnspan=2)
                win_btn = tb.Button(width=12, text="Click here for\nREWARD",bootstyle='success', command=open_url)
                win_btn.grid(row=3, columnspan=2, padx=10, pady=10)
            else:
                user_guess_entry.delete(0, 'end')
                if hint_used == 1:
                    user_guess_entry.insert(0, guess_word[0])  # If hint used, fill in the first letter of the word
                guess_count += 1
                user_guess_entry.focus()
                try_label.config(text=f'"{user_guess}" is not the correct\nword please\nTry Again')
                try_label.grid(row=2, columnspan=2)
                if guess_count == 2:
                    hint_label.config(text="\nDo you want a hint")
                    hint_label.grid(row=4, columnspan=2)
                    hint_btn_yes.config(text="Yes",bootstyle="info", command=show_hint)
                    hint_btn_no.config(text="No",bootstyle="danger", command=hide_hint)
                    hint_btn_yes.grid(row=5, column=0, padx=10, pady=10)
                    hint_btn_no.grid(row=5, column=1, padx=10, pady=10)
                    break
                break
        else:
            user_guess_entry.config(command=None)  # Disable further input if the game is won
            break

# Submit button for guessing
user_guess_submit_btn = tb.Button(width=6, text="Submit", command=guess)
user_guess_submit_btn.grid(row=1, columnspan=2, sticky=tk.E, padx=5, pady=5)

# Start the main event loop to run the GUI
root.mainloop()
