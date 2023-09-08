import tkinter as tk
from tkinter import ttk
import csv

def submit():
    name = entry_name.get()
    age = entry_age.get()
    email = entry_email.get()
    gender = combo_gender.get()
    relationship_type = radio_var.get()
    subscribe_newsletter = check_var.get()

    # Set default values if user doesn't make a selection
    if not gender:
        gender = "Male"
    if not relationship_type:
        relationship_type = "Single"

    # Append default email extension if not provided by the user
    if email and not email.endswith("@gmail.com"):
        email += "@gmail.com"

    with open('data.csv', mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([name, age, email, gender, relationship_type, subscribe_newsletter])

    # Clear input fields after submitting
    entry_name.delete(0, tk.END)
    entry_age.delete(0, tk.END)
    entry_email.delete(0, tk.END)
    combo_gender.set("Male")
    radio_var.set("Single")
    check_var.set(0)

    # Show confirmation message
    confirmation_label.config(text="Data submitted successfully!", fg="green")

root = tk.Tk()
root.title("User Information Form")
root.geometry("400x300")  # Set the window size

# Center the window on the screen
window_width = root.winfo_reqwidth()
window_height = root.winfo_reqheight()
position_right = int(root.winfo_screenwidth() / 2 - window_width / 2)
position_down = int(root.winfo_screenheight() / 2 - window_height / 2)
root.geometry("+{}+{}".format(position_right, position_down))

# Dark mode theme
root.configure(bg="#333333")
default_font = ("Helvetica", 12)

# Labels
tk.Label(root, text="Name:", font=default_font, bg="#333333", fg="white").grid(row=0, column=0, padx=5, pady=5, sticky=tk.W)
tk.Label(root, text="Age:", font=default_font, bg="#333333", fg="white").grid(row=1, column=0, padx=5, pady=5, sticky=tk.W)
tk.Label(root, text="Email:", font=default_font, bg="#333333", fg="white").grid(row=2, column=0, padx=5, pady=5, sticky=tk.W)
tk.Label(root, text="Gender:", font=default_font, bg="#333333", fg="white").grid(row=3, column=0, padx=5, pady=5, sticky=tk.W)
tk.Label(root, text="Relationship Type:", font=default_font, bg="#333333", fg="white").grid(row=4, column=0, padx=5, pady=5, sticky=tk.W)
tk.Label(root, text="Subscribe to Newsletter:", font=default_font, bg="#333333", fg="white").grid(row=5, column=0, padx=5, pady=5, sticky=tk.W)

# Entry boxes
entry_name = tk.Entry(root, font=default_font)
entry_name.grid(row=0, column=1, padx=5, pady=5)
entry_name.focus()  # Set cursor focus on 'name' entry box

entry_age = tk.Entry(root, font=default_font)
entry_age.grid(row=1, column=1, padx=5, pady=5)
entry_email = tk.Entry(root, font=default_font)
entry_email.grid(row=2, column=1, padx=5, pady=5)

# Set default email extension
entry_email.insert(tk.END, "@gmail.com")

# Combo box for gender
combo_gender = ttk.Combobox(root, values=["Male", "Female", "Other"],state='readonly', font=default_font)
combo_gender.grid(row=3, column=1, padx=5, pady=5)
combo_gender.set("Male")  # Set default value for 'gender' as "Male"

# Radio buttons for relationship type
radio_var = tk.StringVar()
radio_single = tk.Radiobutton(root, text="Single", variable=radio_var, value="Single", font=default_font, bg="#333333", fg="white", selectcolor="#333333")
radio_single.grid(row=4, column=1, padx=5, pady=5, sticky=tk.W)
radio_single.select()  # Set default value for 'relationship type' as "Single"

radio_married = tk.Radiobutton(root, text="Married", variable=radio_var, value="Married", font=default_font, bg="#333333", fg="white", selectcolor="#333333")
radio_married.grid(row=4, column=1, padx=5, pady=5, sticky=tk.E)

# Checkbox for newsletter subscription
check_var = tk.IntVar()
check_newsletter = tk.Checkbutton(root, variable=check_var, font=default_font, bg="#333333", fg="white", selectcolor="#333333")
check_newsletter.grid(row=5, column=1, padx=5, pady=5)

# Submit button
submit_button = tk.Button(root, text="Submit", command=submit, font=default_font, bg="#4CAF50", fg="white", activebackground="#45a049")
submit_button.grid(row=6, column=0, columnspan=2, padx=5, pady=10)

# Confirmation message label
confirmation_label = tk.Label(root, font=default_font, bg="#333333", fg="green")
confirmation_label.grid(row=7, column=0, columnspan=2)

root.mainloop()
