#!/bin/python
import tkinter

class MQDSInputGUI:
    def __init__(self, master):
        self.master = master
        master.title("A simple GUI to generate input files for the MQDS package")

        self.choices = []

        irow = 0
        self.label = tkinter.Label(master, text="Welcome to the MQDS input file GUI!").grid(row=0,columnspan=2)
        irow += 1

        #METHOD
        self.make_label(master, "method", my_row=irow)
        self.make_menu(master,"method",self.method_options(), my_row=irow)
        irow += 1

        #CALCULATION
        self.make_label(master, "calculation", my_row=irow)
        self.make_menu(master,"calculation",self.calculation_options(), my_row=irow)
        irow += 1

        #SYSTEM BASIS
        self.make_label(master, "system_basis", my_row=irow)
        self.make_menu(master,"system_basis",self.system_basis_options(), my_row=irow)
        irow += 1
        ++irow

        #NUMBER OF STATES
        self.make_label(master, "nstate", my_row=irow)
        self.make_textbox(master, my_row=irow)
        irow += 1
        ++irow


        #INITIAL FORWARD WAVEFUNCTION STATE
        self.make_label(master, "initstate", my_row=irow)
        self.make_textbox(master, my_row=irow)
        irow += 1
        ++irow

        #INITIAL BACKWARD WAVEFUNCTION STATE
        self.make_label(master, "initstatet", my_row=irow)
        self.make_textbox(master, my_row=irow)
        irow += 1
        ++irow

        #NUMBER OF TRAJECTORIES
        self.make_label(master, "ntraj", my_row=irow)
        self.make_textbox(master, my_row=irow)
        irow += 1

        #NUMBER OF BATH TIME STEPS
        self.make_label(master, "nstep", my_row=irow)
        self.make_textbox(master, my_row=irow)
        irow += 1

        #NUMBER OF SYSTEM STEPS PER BATH STEP
        self.make_label(master, "nlit", my_row=irow)
        self.make_textbox(master, my_row=irow)
        irow += 1

        #NUMBER OF BATH STEPS PER OBSERVATION
        self.make_label(master, "dump", my_row=irow)
        self.make_textbox(master, my_row=irow)
        irow += 1

        #TEMPERATURE
        self.make_label(master, "temperature", my_row=irow)
        self.make_textbox(master, my_row=irow)
        irow += 1

        #SQC-SPECIFIC PARAMETERS
        self.label = tkinter.Label(master, text="~~~SQC-specific Input Parameters~~~").grid(row=irow,columnspan=2)
        irow += 1
        
        #PRINT RESULTING INPUT FILE
        self.make_file = tkinter.Button(master, text="Make Input File", 
                                        command = self.printfile
                                        ).grid(row=irow,columnspan=2)
        irow += 1

        #CLOSE WINDOW
        self.close_button = tkinter.Button(master, text="Close",
                                           command=master.quit
                                           ).grid(row=irow,columnspan=2)

    def printfile(self):
        print("Still need to make printable!")
    
    def make_label(self,master,my_label,my_row):
        self.label = tkinter.Label(master, text=my_label).grid(row=my_row,column=0)

    def make_menu(self,master,my_type,my_options,my_row):
        my_selection = tkinter.StringVar(master)
        my_selection.set(my_options[0]) #sets default
        self.selection = tkinter.OptionMenu(master, my_selection, *my_options)
        self.selection.grid(row=my_row,column=1)
        
    def make_textbox(self,master,my_row):
        self.selection = tkinter.Entry(master)
        self.selection.grid(row = my_row, column=1)

    def method_options(self):
        method_options = [
            "pldm",
            "ipldm",
            "sqc",
            "lsc",
            "equilibrium"
            ]
        return method_options
        
    def calculation_options(self):
        calculation_options = [
            "redmat",
            "absorption",
            "circular_dichroism",
            "2des",
            "1dpp"
            ]
        return calculation_options

    def system_basis_options(self):
        system_basis_options = [
            "site",
            "exciton"
            ]
        return system_basis_options

root = tkinter.Tk()
my_gui = MQDSInputGUI(root)
root.mainloop()
