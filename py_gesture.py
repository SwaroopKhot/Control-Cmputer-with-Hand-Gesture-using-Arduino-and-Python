import serial
import time
import pyautogui

# Plot-real-time :
#import psutil
import matplotlib.pyplot as plt

from itertools import count
from matplotlib.animation import FuncAnimation  # -- important for real time plots --


# For plot:
plt.style.use('seaborn')

fig, (ax1, ax2) = plt.subplots(2)
fig.suptitle('Plot on Distance v/s Time measured by sensors')


j=0
t1_value, t2_value, y_value, z_value = [], [], [], []
index1 = count()
index2 = count()

#Create Serial Port :
ArdunioSerial = serial.Serial('com10', 9600) 






def animate(i):
	

	incoming = str(ArdunioSerial.readline())

	incoming = incoming.lstrip("b")
	incoming = incoming.strip("'")
	incoming = incoming.rstrip("\\r\\n")
	print(incoming)


	# Left sensor data :

	incoming1 = incoming
	left_sensor_reading = 0
	if incoming1[0] == 'L':
		incoming_left = incoming1.lstrip("L:")

		t1_value.append(next(index1))
		y_value.append(incoming_left)

		xlim1 = int(next(index1))

		
		ax1.plot(t1_value, y_value, color='b')
		ax1.legend(['Left sensor'], loc='upper left')


		ax1.set_xlabel('Time (in sec)')
		ax1.set_ylabel('Left sensor(in cm)')
		ax1.set_xlim(left=max(1,xlim1-60), right=xlim1+60)


	# Right Sensor data :
	incoming2 = incoming

	if incoming2[0] == 'R':	
		incoming_right = incoming2.lstrip("R:")

		t2_value.append(next(index2))
		z_value.append(incoming_right)

		plt.cla() # -- makes color constant --
		xlim2 = int(next(index2))

		ax2.plot(t2_value, z_value, color='orange')
		ax2.legend(['Right sensor'], loc='upper left')
		ax2.set_xlabel('Time (in sec)')
		ax2.set_ylabel('right sensor(in cm)')
		ax2.set_xlim(left=max(1,xlim2-60), right=xlim2+60)

	# Control Keyboard Keys :

	# both Sensor :
	if "Play/Pause" in incoming:
		pyautogui.typewrite(['space'], 0.2)

	
	# LEFT Sensor :
	if 'Escape' in incoming:
		pyautogui.press('backspace')
		pyautogui.keyUp('win')

	if 'CTabs' in incoming:
		pyautogui.keyDown('win')


	if 'Vdow' in incoming :
		pyautogui.hotkey('ctrl','down')
		pyautogui.keyUp('win')

	if 'Vup' in incoming :
		pyautogui.hotkey('ctrl','up')
		pyautogui.keyUp('win')


	# RIGHT Sensor :
	if 'Ente' in incoming:
		pyautogui.press('enter')
		pyautogui.keyUp('win')

	if 'Tab' in incoming:
		pyautogui.press('tab')
		pyautogui.keyUp('win')

	if 'FForward' in incoming:
		pyautogui.hotkey('ctrl','right')
		pyautogui.keyUp('win')

	if 'FRewind' in incoming:
		pyautogui.hotkey('ctrl','left')
		pyautogui.keyUp('win')

			









ani = FuncAnimation(fig, animate, interval=100)
plt.tight_layout()
plt.show()
print('-------------')
