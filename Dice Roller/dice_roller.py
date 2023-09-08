import random 
import tkinter as ttk

root=ttk.Tk()
root.geometry('700x450')
root.resizable(0,0)

label=ttk.Label(root,text="",font=("time",260))
label.pack(padx=10,pady=10)

def roll():
    dice=['\u2680','\u2681','\u2682','\u2683','\u2684','\u2685']
    label.configure(text=f'{random.choice(dice)}{random.choice(dice)}')
    label.pack()

btn=ttk.Button(root,text="Roll",width=40,
               height=5,font=10,bg='white',
               bd=2,command=roll)

btn.pack(padx=10,pady=10)

root.mainloop()    