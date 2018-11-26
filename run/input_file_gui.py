#!/bin/python
import tkinter

class MQDSInputGUI:
    def __init__(self, master):
        self.master = master
        master.title("A simple GUI to generate input files for the MQDS package")

        self.choices = {}
        self.my_selection = {}

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

        #BATH POTENTIAL
        self.make_label(master, "bath_potential", my_row=irow)
        self.make_menu(master,"bath_potential",self.bath_potential_options(), my_row=irow)
        irow += 1

        #NUMBER OF STATES
        self.make_label(master, "nstate", my_row=irow)
        self.make_textbox(master, my_row=irow)
        irow += 1

        #INITIAL FORWARD WAVEFUNCTION STATE
        self.make_label(master, "initstate", my_row=irow)
        self.make_textbox(master, my_row=irow)
        irow += 1

        #INITIAL BACKWARD WAVEFUNCTION STATE
        self.make_label(master, "initstatet", my_row=irow)
        self.make_textbox(master, my_row=irow)
        irow += 1

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

        #ZERO-POINT ENERGY
        self.make_label(master, "zpe", my_row=irow)
        self.make_textbox(master, my_row=irow)
        irow += 1

        #WINDOW SHAPE
        self.make_label(master, "window_shape", my_row=irow)
        self.make_menu(master,"window_shape",self.window_shape_options(), my_row=irow)
        irow += 1
        
        #PRINT RESULTING INPUT FILE
        self.make_file = tkinter.Button(master, text="Make Input File", 
                                        command = lambda: self.printfile()
                                        ).grid(row=irow,columnspan=2)
        irow += 1

        #CLOSE WINDOW
        self.close_button = tkinter.Button(master, text="Close",
                                           command=master.quit
                                           ).grid(row=irow,columnspan=2)
        irow += 1


    def printfile(self):
        #self.choices["method"] = self.my_selection[1].get()
        #print(self.choices)
        with open('run.in','w') as f:
            f.write( "{} {}\n".format("method", self.my_selection[1].get()) )
            f.write( "{} {}\n".format("calculation", self.my_selection[2].get()) )
            f.write( "{} {}\n".format("system_basis", self.my_selection[3].get()) )
            f.write( "{} {}\n".format("bath_potential", self.my_selection[4].get()) )
            f.write( "{} {}\n".format("nstate", self.my_selection[5].get()) )
            f.write( "{} {}\n".format("initstate", self.my_selection[6].get()) )
            f.write( "{} {}\n".format("initstatet", self.my_selection[7].get()) )
            f.write( "{} {}\n".format("ntraj", self.my_selection[8].get()) )
            f.write( "{} {}\n".format("nstep", self.my_selection[9].get()) )
            f.write( "{} {}\n".format("nlit", self.my_selection[10].get()) )
            f.write( "{} {}\n".format("dump", self.my_selection[11].get()) )
            f.write( "{} {}\n".format("temperature", self.my_selection[12].get()) )
            ####################LINE BREAK###################
            f.write( "{} {}\n".format("zpe", self.my_selection[14].get()) )
            f.write( "{} {}\n".format("window_shape", self.my_selection[15].get()) )

    
    def make_label(self,master,my_label,my_row):
        self.label = tkinter.Label(master, text=my_label).grid(row=my_row,column=0)

    def make_menu(self,master,my_type,my_options,my_row):
        self.my_selection[my_row] = tkinter.StringVar(master)
        self.my_selection[my_row].set(my_options[0]) #sets default
        self.selection = tkinter.OptionMenu(master, self.my_selection[my_row], *my_options)
        self.selection.grid(row=my_row,column=1)

    def make_textbox(self,master,my_row):
        self.selection = tkinter.Entry(master)
        self.selection.grid(row = my_row, column=1)
        self.my_selection[my_row] = self.selection

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
            "exciton",
            "vibronic_site",
            "vibronic_exciton"
        ]
        return system_basis_options

    def bath_potential_options(self):
        bath_potential_options = [
        "harmonic"
        ]
        return bath_potential_options

    def window_shape_options(self):
        window_shape_options = [
            "square",
            "triangular"
        ]
        return window_shape_options

root = tkinter.Tk()
my_gui = MQDSInputGUI(root)
root.mainloop()