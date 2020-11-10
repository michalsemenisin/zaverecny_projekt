from tkinter import *
import tkinter as tk                                                        # import tkinter knihovny
import serial                                                               # import Serial knihovny
import random                                                               # pouzito na ziskani nahodnych hodnot pro funkci nahodne pozice ramena





#                                  
#                   Hodnoty znamenají:       -+1 = rameno vlevo/vpravo
#                                            -+2 = rameno nahoru/dolu
#                                             3 = reset ramena
#                                             4 = nahodna pozice ramena
#

ArduinoSerial = serial.Serial('com1', 9600) # Vytvoreni arduino serial objetku


def callback(value,code):                       # Value predava hodnotu '5,10,15' - stupne,  code urcuje zda rameno jede nahoru/dolu/vlevo/vpravo/reset/nahodna pozice
    global holdsum                              # Uklada pocet stupnu aby nepresahl 0<x<180 pro pohyb doprava a doleva
    global holdsum2                             # Uklada pocet stupnu aby nepresahl 0<x<180 pro pohyb nahoru a dolu
    global Degrees                              # Uklada aktualni prepinacovy vyber stupnu

    if((code == 1) or (code == -1)):                # Kontrola zda code je vlevo ci vpravo
        holdsum=holdsum+(code*Degrees)              # Uklada bezici počet levých/pravých stupnu. Vynasobenim (1) -  kladna cisla nebo (-1) zaporna cisla
        if(holdsum < 0):                            # Aby nedoslo k tomu ze stupne pujdou pod 0 stupnu - serva nemohou pod 0 stupnu
            holdsum = 0                             # Natvrdo nastaveni 0
        if(holdsum > 180):                          # Aby nedoslo k tomu ze stupne pujdou nad 180 stupnu - serva nemohou nad  180 stupnu
            holdsum = 180                           # Natvrdo nastaveni 180
        textBox1.delete('1.0', tk.END)              # Vymazani textoveho pole
        textBox1.insert(tk.INSERT,holdsum)          # Zobrazeni novych stupnu
        textBox3.delete('1.0', tk.END)              # Vymazani textoveho pole
        textBox3.insert(tk.INSERT,holdsum)          # Zobrazeni novych stupnu
        
        ArduinoSerial.write(str(Degrees).encode())  # Odeslani prvnich cisel s poctem stupnu do Arduina
        ArduinoSerial.write(','.encode())           # Odeslani oddelovaci carky pro signalizaci prvniho ze 2 cisel odeslanych do arduina
        ArduinoSerial.write(str(code).encode())     # Odeslani 'code' - pro nahoru/dolu, doleva/doprava, ......
        ArduinoSerial.write(','.encode())           # Odeslani oddelovaci carky pro signalizaci prvniho ze 2 cisel odeslanych do arduina

    if((code == 2) or (code == -2)):                # Kontrola zda code je nahoru ci dolu
        holdsum2=holdsum2+(int(code/2)*Degrees)     # Musime vydelit 2 abychom ziskali +-1 pro násobení
        if(holdsum2 < 0):                           # Aby nedoslo k tomu ze stupne pujdou pod 0 stupnu - serva nemohou pod 0 stupnu
            holdsum2 = 0                            # Natvrdo nastaveni 0
        if(holdsum2 > 180):                         # Aby nedoslo k tomu ze stupne pujdou nad 180 stupnu - serva nemohou nad  180 stupnu
            holdsum2 = 180                          # Natvrdo nastaveni 180
        textBox2.delete('1.0', tk.END)              # Vymazani textoveho pole
        textBox2.insert(tk.INSERT,holdsum2)         # Zobrazeni novych stupnu
        textBox5.delete('1.0', tk.END)              # Vymazani textoveho pole
        textBox5.insert(tk.INSERT,holdsum2)         # Zobrazeni novych stupnu

        ArduinoSerial.write(str(Degrees).encode())  # Odeslani prvnich cisel s poctem stupnu do Arduina
        ArduinoSerial.write(','.encode())           # Odeslani oddelovaci carky pro signalizaci prvniho ze 2 cisel odeslanych do arduina
        ArduinoSerial.write(str(code).encode())     # Odeslani 'code' - pro nahoru/dolu, doleva/doprava, ......
        ArduinoSerial.write(','.encode())           # Odeslani oddelovaci carky pro signalizaci prvniho ze 2 cisel odeslanych do arduina

    if(code == 3):
        ArduinoSerial.write(str(Degrees).encode())  # Odeslani prvnich cisel s poctem stupnu do Arduina
        ArduinoSerial.write(','.encode())           # Odeslani oddelovaci carky pro signalizaci prvniho ze 2 cisel odeslanych do arduina
        ArduinoSerial.write(str(code).encode())     # Odeslani 'code' - pro nahoru/dolu, doleva/doprava, ......
        ArduinoSerial.write(','.encode())           # Odeslani oddelovaci carky pro signalizaci prvniho ze 2 cisel odeslanych do arduina
        textBox1.delete('1.0', tk.END)              # Vymazani textoveho pole
        textBox1.insert(tk.INSERT,'90')             # display the new degrees.
        textBox2.delete('1.0', tk.END)              # Vymazani textoveho pole
        textBox2.insert(tk.INSERT,'0')              # Inicializace hodnoty
        textBox3.delete('1.0', tk.END)              # Vymazani textoveho pole
        textBox3.insert(tk.INSERT,'90')             # Inicializace hodnoty
        textBox4.delete('1.0', tk.END)              # Vymazani textoveho pole
        textBox4.insert(tk.INSERT,'165')            # Inicializace hodnoty
        textBox5.delete('1.0', tk.END)              # Vymazani textoveho pole
        textBox5.insert(tk.INSERT,'0')              # Inicializace hodnoty
        textBox6.delete('1.0', tk.END)              # Vymazani textoveho pole
        textBox6.insert(tk.INSERT,'0')              # Inicializace hodnoty
        textBox7.delete('1.0', tk.END)              # Vymazani textoveho pole
        textBox7.insert(tk.INSERT,'OFF')            # Inicializace hodnoty
        holdsum=90                                  # Reset hodnoty vlevo/vpravo
        holdsum2=0                                  # Reset hodnoty nahoru/dolu
                                                      

    if(code == 4):
        textBox7.delete('1.0', tk.END)                              # Vymazani textoveho pole
        textBox7.insert(tk.INSERT,'ON')                             # Had to leave 'ON' could not set from 'ON' to 'OFF'; only 'OFF' shows up.
        textBox7.update()                                           # Zapsani do textoveho pole
        ArduinoSerial.write(str(Degrees).encode())                  # Odeslani prvnich cisel s poctem stupnu do Arduina
        ArduinoSerial.write(','.encode())                           # Odeslani oddelovaci carky pro signalizaci prvniho ze 2 cisel odeslanych do arduina
        ArduinoSerial.write(str(code).encode())                     # Odeslani 'code' - pro nahoru/dolu, doleva/doprava, ......
        ArduinoSerial.write(','.encode())                           # Odeslani oddelovaci carky pro signalizaci posledniho ze 2 cisel odeslanych do arduina
        root.after(2000)                                            # Pockat 2 vteriny
        for x in range(5):                                          # will print 1 random values of numbers between 1 and 180.
            textBox3.delete('1.0', tk.END)                          # Vymazani textoveho pole
            textBox3.insert(tk.INSERT,random.randint(1,181))        # Generace nahodneho cisla
            textBox3.update()                                       # Zapsani do textoveho pole
            textBox4.delete('1.0', tk.END)                          # Vymazani textoveho pole
            textBox4.insert(tk.INSERT,random.randint(1,181))        # Generace nahodneho cisla
            textBox4.update()                                       # Zapsani do textoveho pole
            textBox5.delete('1.0', tk.END)                          # Vymazani textoveho pole
            textBox5.insert(tk.INSERT,random.randint(1,181))        # Generace nahodneho cisla
            textBox5.update()                                       # Zapsani do textoveho pole
            textBox6.delete('1.0', tk.END)                          # Vymazani textoveho pole
            textBox6.insert(tk.INSERT,random.randint(1,181))        # Generace nahodneho cisla
            textBox6.update()                                       # Zapsani do textoveho pole
            root.after(2000)                                        # Pockat 2 vteriny
        textBox7.delete('1.0', tk.END)                              # Vymazani textoveho pole
        textBox7.insert(tk.INSERT,'OFF')                            
                                                                    
root = Tk()

root.geometry("500x400")                                            # Velikost okna
root.config(background="#FEF1AB")                                   # Pozadi
radioButtonVar = tk.IntVar()                                        # Urceno k tomu aby prepinace byly nevyplnene pri zapnuti programu
holdsum=0                                                           # Uklada pocet stupnu aby nepresahl 0<x<180 pro pohyb doprava a doleva
holdsum2=0                                                          # Uklada pocet stupnu aby nepresahl 0<x<180 pro pohyb nahoru a dolu
Degrees=0                                                           # Nastavit pocet stupnu na 0


#################################################################
root.title("Ovladani ramena")             

#################### tlacitka ##################
labelMove1 = Label(root, background="#EFFEAC",  font = ('Arial' , 10),text="ARM RIGHT-LEFT")   # Text nad textovym polem
labelMove1.place(x=70,y=0)                                                                         
labelMove2 = Label(root, background="#EFFEAC",  font = ('Arial' , 10),text="ARM UP-DOWN")      # Text nad textovym polem 
labelMove2.place(x=280,y=0)                                                                        

MoveLeftButton = Button(root, bd=3,text="Arm Left")                         # Tlacitko pro pohyb doleva
MoveLeftButton.bind('<Button-1>',lambda event,arg=1:callback(0,1))          # Tato lambda funkce umožnuje levym tlačítkem na myši aktivovat funkci
MoveLeftButton.place(x=40, y=50)                                           

MoveRightButton = Button(root, bd=3,text="Arm Right")                       # Tlacitko pro pohyb doprava
MoveRightButton.bind('<Button-1>',lambda event,arg=1:callback(0,-1))        # Tato lambda funkce umožnuje levym tlačítkem na myši aktivovat funkci
MoveRightButton.place(x=140, y=50)                                         

textBox1 = Text(root,height=1,width=3,bd=2)                                 # Textove pole na ulozeni stupnu  
textBox1.place(x=110,y=22)                                                  
textBox1.insert(tk.INSERT,0)                                                # Docasna hodnota do textoveho pole

################################################################
MoveRightButton = Button(root, bd=3,text="Arm Up")                          # Tlacitko pro pohyb nahoru
MoveRightButton.bind('<Button-1>',lambda event,arg=1:callback(0,2))         # Tato lambda funkce umožnuje levym tlačítkem na myši aktivovat funkci
MoveRightButton.place(x=310, y=50)                                         

MoveRightButton = Button(root, bd=3,text="Arm Down")                        # Tlacitko pro pohyb dolu
MoveRightButton.bind('<Button-1>',lambda event,arg=1:callback(0,-2))        # Tato lambda funkce umožnuje levym tlačítkem na myši aktivovat funkci
MoveRightButton.place(x=300, y=90)                                         

textBox2 = Text(root,height=1,width=3,bd=2)                                 # Textove pole na ulozeni stupnu
textBox2.place(x=320,y=22)                                                 
textBox2.insert(tk.INSERT,0)                                                # Docasna hodnota do textoveho pole

#################################################################
labelMode = tk.Label(root,background="#EFFEAC", font = ('Arial' , 10),text="MODE")  # MODE text
labelMode.place(x=205,y=109)                                                           

ArmResetButton = Button(root, bd=3,text="Reset Arm")                        # Tlacitko Reset Arm
ArmResetButton.bind('<Button-1>',lambda event,arg=1:callback(0,3))          # Tato lambda funkce umožnuje levym tlačítkem na myši aktivovat funkci
ArmResetButton.place(x=195, y=240)                                         

ArmRandomButton = Button(root, bd=3,text="Random Move")                     # Tlacitko Random move
ArmRandomButton.bind('<Button-1>',lambda event,arg=1:callback(0,5))         # Tato lambda funkce umožnuje levym tlačítkem na myši aktivovat funkci
ArmRandomButton.place(x=185, y=200)                                        

textBox7 = Text(root,height=1,width=3,bd=2)                                 # Textové pole pro ON/OFF
textBox7.place(x=210,y=130)                                                
textBox7.insert(tk.INSERT,'OFF')                                            # Docasna hodnota OFF

#################################################################
labelRadioButton = tk.Label(root,background="#EFFEAC", font = ('Arial' , 10),text="DEGREE\nSELECTION")          # Text Degree Selection
labelRadioButton.place(x=300,y=165)                                                                                

radioButton1 = Radiobutton(root,background="#EFFEAC",variable=radioButtonVar,value=5,text=" 5 deg")             # Nastavi hodnotu tlacitka na 5 stupnu
radioButton1.bind('<Button-1>',lambda event,arg=1:callback(5,0))                                                    # Tato lambda funkce umožnuje levym tlačítkem na myši aktivovat funkci
radioButton1.place(x=301,y=200)                                                                                    

radioButton2 = Radiobutton(root,background="#EFFEAC",variable=radioButtonVar,padx=10,value=10,text="10 deg")    # Nastavi hodnotu tlacitka na 10 stupnu
radioButton2.bind('<Button-1>',lambda event,arg=1:callback(10,0))                                                   # Tato lambda funkce umožnuje levym tlačítkem na myši aktivovat funkci
radioButton2.place(x=292,y=225)                                                                                    

radioButton3 = Radiobutton(root,background="#EFFEAC",variable=radioButtonVar,padx=10,value=15,text="15 deg")    # Nastavi hodnotu tlacitka na 15 stupnu
radioButton3.bind('<Button-1>',lambda event,arg=1:callback(15,0))                                                   # Tato lambda funkce umožnuje levym tlačítkem na myši aktivovat funkci
radioButton3.place(x=292,y=250)                                                                                        

#########################################################################################
labelArm = tk.Label(root,background="#EFFEAC", font = ('Arial' , 10),text="ARM\nDEGREES")   # Text Arm Degrees
labelArm.place(x=100,y=120)                                                                    
                    
labelBase = tk.Label(root,background="#EFFEAC", text="Base: ")
labelBase.place(x=40, y=160)                                                                   
textBox3 = Text(root,height=1,width=3,bd=2)                                                     # Textové pole na zobrazeni stupnu
textBox3.place(x=120,y=160)                                                                     
textBox3.insert(tk.INSERT,'90')                                                                 # Docasna hodnota

labelShoulder = tk.Label(root, background="#EFFEAC",text="Shoulder: ")
labelShoulder.place(x=40, y=190)                                                               
textBox4 = Text(root,height=1,width=3,bd=2)                                                     # Textové pole na zobrazeni stupnu
textBox4.place(x=120,y=190)                                                                    
textBox4.insert(tk.INSERT,'165')                                                                # Docasna hodnota


labelElbow = tk.Label(root, background="#EFFEAC",text="Elbow: ")
labelElbow.place(x=40, y=220)                                                                  
textBox5 = Text(root,height=1,width=3,bd=2)                                                     # Textové pole na zobrazeni stupnu
textBox5.place(x=120,y=220)                                                                    
textBox5.insert(tk.INSERT,'0')                                                                  # Docasna hodnota


labelWrist = tk.Label(root,background="#EFFEAC", text="Wrist: ")
labelWrist.place(x=40, y=250)                                                                     
textBox6 = Text(root,height=1,width=3,bd=2)                                                     # Textové pole na zobrazeni stupnu
textBox6.place(x=120,y=250)                                                                    
textBox6.insert(tk.INSERT,'0')                                                                  # Docasna hodnota


##########################################################################################        
root.mainloop()                                                                                 # Start programu

        



