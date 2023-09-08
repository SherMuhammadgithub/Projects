                                    ### Version-2

# importing the necesarry modules
import tkinter as tk
import ttkbootstrap as tb
from tkinter import ttk
import pdb


# gui skeleton
root=tb.Window(themename="darkly")
root.geometry("450x360")
root.resizable(0,0)
root.position_center()
root.title("Calculator")


# input box entered data stored here
expression=''

# input box where all the data is showed
input_box=tk.Text(root,height=2,width=35)
input_box.grid(row=0,column=0,columnspan=4)
input_box.focus()

# button frame where all the buttons are located
buttons=tk.LabelFrame(root)
buttons.grid(row=1, column=0,sticky=tk.W)
op=''
# clear all ('C') button functionality
def del_all():
    global expression,op
    op=''
    input_box.delete(1.0,tk.END)
    expression=''

# clear all ('C') button
clear_all=tb.Button(buttons,text="C",width=6,bootstyle='danger',command=del_all)
clear_all.grid(row=0,column=0,sticky=tk.W,padx=5,pady=5)

# delete one single digit button functionality
def del_one():
    global expression
    current_content = input_box.get("1.0", tk.END)
    if current_content.strip():  # Check if there is any content in the Text widget
        new_content = current_content[:-2]  # Remove the last character and newline
        input_box.delete("1.0", tk.END)  # Clear the current content
        input_box.insert("1.0", new_content)  # Insert the updated content
        expression=expression[:-1]

# delete one single digit button
clear_one=tb.Button(buttons,text='⌫',width=6,bootstyle='danger',command=del_one)
clear_one.grid(row=0,column=2,sticky=tk.W,padx=5,pady=5)


# plus button
plus_btn=tb.Button(buttons,text='+',width=6,bootstyle='warning',command=lambda:action("+"))
plus_btn.grid(row=3,column=3,sticky=tk.W,padx=5,pady=5)

# minus button
minus_btn=tb.Button(buttons,text='-',width=6,bootstyle='warning',command=lambda:action("-"))
minus_btn.grid(row=2,column=3,sticky=tk.W,padx=5,pady=5)

# multiply button
multiply_btn=tb.Button(buttons,text='x',width=6,bootstyle='warning',command=lambda:action("*"))
multiply_btn.grid(row=1,column=3,sticky=tk.W,padx=5,pady=5)

# divide button
divide_btn=tb.Button(buttons,text='÷',width=6,bootstyle='warning',command=lambda:action("/"))
divide_btn.grid(row=0,column=3,sticky=tk.W,padx=5,pady=5)

# power function
def power():
    global op
    op=""
    op='^'
    action("^")

# power button
power_btn=tb.Button(buttons,text='^',width=6,bootstyle='warning',command=power)
power_btn.grid(row=0,column=1,sticky=tk.W,padx=5,pady=5)

previous=''
n1=0
n2=0
res=0

# equal function
def equal():
    global n1,n2,res,op,expression,previous
    expression=input_box.get(1.0,'end')
    print(expression)
    try:
        if op=="^":
            previous=expression
            print(previous)
            n1,n2=expression.split('^')
            res=int(n1)**int(n2)
            input_box.delete(1.0,'end')
            input_box.insert(1.0,res)
            expression=str(res)
            op=""
        
    except:
        error="An error occured"
        input_box.delete(1.0,'end')
        input_box.insert(1.0,error)
        expression=''
        op=""
    else:
        try:
            previous=expression
            print(expression)
            expression=str(eval(expression))      # eval= evaluate's all of the expression
                                                  # and returns the answer 
            input_box.delete(1.0,'end')                   
            input_box.insert(1.0, expression)
    
        except ZeroDivisionError:
            error="Can't Divide By Zero"
            input_box.delete(1.0,'end')
            input_box.insert(1.0,error)
            expression=''
    
        except:
            error="Unknown Error Occured"    
            input_box.delete(1.0,'end')
            input_box.insert(1.0,error)
            expression=''

# equal button
equal_btn=tb.Button(buttons,text='=',width=6,bootstyle='success',command=equal)
equal_btn.grid(row=4,column=3,sticky=tk.W,padx=5,pady=5)


def prev():
    global previous,expression
    expression=previous
    input_box.delete(1.0,'end')
    input_box.insert(1.0,expression)

prev_btn=tb.Button(buttons,text='Prev',width=6,bootstyle='danger',command=prev)
prev_btn.grid(row=4,column=2,sticky=tk.W,padx=5,pady=5)



# button pressed shown on input box
def action(n):
    global expression
    expression+=str(n)
    # expression+=n
    input_box.delete(1.0,'end')
    input_box.insert(1.0,expression)

rw=1
cl=0
for i in range(9,-1,-1):
    ttk.Button(buttons,text=i,width=6
           ,command=lambda num=i: action(num)).grid(row=rw,column=cl
                                            ,sticky=tk.W,padx=5,pady=5)
    cl+=1
    if cl==3:
        rw+=1
        cl=0


root.mainloop()
