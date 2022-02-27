import speech_recognition as sr
import serial


board = serial.Serial('COM5',9600)

listener = sr.Recognizer()

def listen():
		
	with sr.Microphone() as source:
		print("listening...");
		voice = listener.listen(source)
		command = listener.recognize_google(voice)
		
	return command
		
while 1<10:
	try:
		board.write(str.encode(listen()))	
	except:
		print("errorcausematveydebil")
